#include <stdafx.hpp>

#include <chrono>

#include <App.hpp>

#define RED4EXT_EXPORT extern "C" __declspec(dllexport)

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

            uint32_t time{};
            RED4ext::ExecuteFunction("gameTimeSystem", "GetGameTime", &time);

            auto days = time / 0x15180;
            auto hours = (time % 0x15180 / 0x0E10);
            auto minutes = (time % 0x0E10 / 0x3C);
            auto seconds = (time % 0x3C);
            spdlog::debug(L"GetGameTime(): {} {} {:02}:{:02}:{:02}", time, days, hours, minutes, seconds);

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
                spdlog::debug(L"GetGameTime(): {} {} {:02}:{:02}:{:02}", time, days, hours, minutes, seconds);

                auto engine = RED4ext::CGameEngine::Get();
                auto unk10 = engine->framework->gameInstance;

                RED4ext::CString item("Items.Jacket_03_old_04");
                RED4ext::CString quantity("1");
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
