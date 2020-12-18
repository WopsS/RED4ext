#include <stdafx.hpp>
#include <RED4ext/RED4ext.hpp>

#include <App.hpp>
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

        int32_t time;
        RED4ext::ExecuteFunction("gameTimeSystem", "GetGameTime", stack, time);

        spdlog::debug(L"GetGameTime(): {} {}:{}:{}", time / 0x15180, (time % 0x15180 / 0x0E10), (time % 0x0E10 / 0x3C),
                      (time % 0x3C));
    }
}

RED4EXT_EXPORT void OnShutdown()
{
    auto app = RED4ext::Playground::App::Get();
    app->Shutdown();
}
