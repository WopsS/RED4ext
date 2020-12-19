#include <stdafx.hpp>

#include <chrono>

#include <App.hpp>
#include <RED4ext/RED4ext.hpp>
#include <RED4ext/REDreverse/CStackFrame.hpp>
#include <RED4ext/Scripting.hpp>

RED4EXT_EXPORT void OnBaseInitialization()
{
    auto app = RED4ext::Playground::App::Get();
    app->Init();
}

RED4EXT_EXPORT void OnInitialization()
{
}

RED4EXT_EXPORT void OnUpdate()
{
    auto app = RED4ext::Playground::App::Get();
    app->Run();

    {
        char byteCode[1]{};

        RED4ext::REDreverse::CStackFrame stack;
        stack.byteCode = byteCode;

        uint32_t time;
        RED4ext::ExecuteFunction("gameTimeSystem", "GetGameTime", stack, time);

        auto days = time / 0x15180;
        auto hours = (time % 0x15180 / 0x0E10);
        auto minutes = (time % 0x0E10 / 0x3C);
        auto seconds = (time % 0x3C);

        spdlog::debug(L"GetGameTime(): {} {}:{}:{}", days, hours, minutes, seconds);
    
        static auto last = std::chrono::high_resolution_clock::now();
        auto now = std::chrono::high_resolution_clock::now();

        using namespace std::chrono_literals;

        // Every 1 minute, skip time by 6 hours, 5 minutes and 30 seconds.
        if ((now - last) > 1min)
        {
            char byteCode[] = {
                0x06, 0x00, 0x00, 0x00, 0x00,   // Int32Const hours + 6
                0x06, 0x00, 0x00, 0x00, 0x00,   // Int32Const minutes + 5
                0x06, 0x00, 0x00, 0x00, 0x00,   // Int32Const seconds + 30
                0x26,                           // ParamEnd
                0x0                             // Nop

            };

            *(int32_t*)(&byteCode[1]) = hours + 6;
            *(int32_t*)(&byteCode[6]) = minutes + 5;
            *(int32_t*)(&byteCode[11]) = seconds + 30;

            RED4ext::REDreverse::CStackFrame stack;
            stack.byteCode = byteCode;

            int32_t time;
            RED4ext::ExecuteFunction("gameTimeSystem", "SetGameTimeByHMS", stack, time);

            last = now;
        }
    }
}

RED4EXT_EXPORT void OnShutdown()
{
    auto app = RED4ext::Playground::App::Get();
    app->Shutdown();
}
