#include <stdafx.hpp>

#include <chrono>

#include <App.hpp>
#include <RED4ext/RED4ext.hpp>
#include <RED4ext/REDreverse/CString.hpp>
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
        static auto lastGet = std::chrono::high_resolution_clock::now();
        static auto lastSet = std::chrono::high_resolution_clock::now();
        auto now = std::chrono::high_resolution_clock::now();

        using namespace std::chrono_literals;
        if ((now - lastGet) >= 10s)
        {
            lastGet = now;

            auto rtti = RED4ext::REDreverse::CRTTISystem::Get();
            uint32_t time{};
            RED4ext::ExecuteFunction("gameTimeSystem", "GetGameTime", &time);

            auto days = time / 0x15180;
            auto hours = (time % 0x15180 / 0x0E10);
            auto minutes = (time % 0x0E10 / 0x3C);
            auto seconds = (time % 0x3C);
            spdlog::debug(L"GetGameTime(): {} {} {}:{}:{}", time, days, hours, minutes, seconds);

            if ((now - lastSet) >= 1min)
            {
                lastSet = now;

                hours += 3;
                minutes += 30;
                seconds += 10;
                
                RED4ext::ExecuteFunction("gameTimeSystem", "SetGameTimeByHMS", nullptr, hours, minutes, seconds);
                RED4ext::ExecuteFunction("gameTimeSystem", "GetGameTime", &time);

                days = time / 0x15180;
                hours = (time % 0x15180 / 0x0E10);
                minutes = (time % 0x0E10 / 0x3C);
                seconds = (time % 0x3C);
                spdlog::debug(L"GetGameTime(): {} {} {}:{}:{}", time, days, hours, minutes, seconds);

                auto rtti = RED4ext::REDreverse::CRTTISystem::Get();
                auto gameInstance = rtti->GetType(RED4ext::FNV1a("ScriptGameInstance"));

                auto test = *(uintptr_t*)(0x1442FD030 - 0x140000000 + (uintptr_t)GetModuleHandle(nullptr));
                auto test2 = &test;

                auto engine = RED4ext::REDreverse::CGameEngine::Get();
                auto unk10 = engine->framework->unk10;

                RED4ext::REDreverse::CString item("Items.Jacket_03_old_04");
                RED4ext::REDreverse::CString quantity("1");
                RED4ext::ExecuteGlobalFunction("AddToInventory", nullptr, unk10, item, quantity);
            }
        }
    }
}

RED4EXT_EXPORT void OnShutdown()
{
    auto app = RED4ext::Playground::App::Get();
    app->Shutdown();
}
