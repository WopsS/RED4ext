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

#include <RED4ext/REDfunc.hpp>
#include <RED4ext/REDptr.hpp>

struct Unk523
{
    int64_t unk0;
    uint64_t unk8;
};

struct CScriptableStackFrame
{
    int64_t vtbl;
    int64_t unk8;
    int64_t unk10;
    int64_t scriptable18;
    int64_t scriptable20;
    int64_t unk28;
    int64_t args;
    int32_t argCount;
    int64_t unk40;
};


union REDString_union
{
    char* ptr;
    char str[20];
};

struct REDString
{
    REDString_union str;
    uint32_t length;
    uint64_t maxSize;
};

RED4EXT_EXPORT void OnUpdate()
{
    auto app = RED4ext::Playground::App::Get();
    app->Run();

    {
        static auto last = std::chrono::high_resolution_clock::now();
        auto now = std::chrono::high_resolution_clock::now();

        using namespace std::chrono_literals;

        // Every 1 minute, skip time by 6 hours, 5 minutes and 30 seconds.
        if ((now - last) > 1min)
        {
            last = now;

            auto rtti = RED4ext::REDreverse::CRTTISystem::Get();

            auto name = RED4ext::FNV1a("AddToInventory");
            auto func = rtti->GetGloblaFunction(name);

            auto type = rtti->GetType<RED4ext::REDreverse::CClass*>(RED4ext::FNV1a("cpPlayerSystem"));
            auto scriptGameInstance = rtti->GetType<RED4ext::REDreverse::CClass*>(RED4ext::FNV1a("ScriptGameInstance"));

            auto engine = RED4ext::REDreverse::CGameEngine::Get();
            auto unk10 = engine->framework->unk10;
            auto scriptable = unk10->GetTypeInstance(type);

            uint64_t a1;
            using test_t = void (*)(void* a1, uintptr_t a2);
            RED4ext::REDfunc<test_t> test(0x140208220 - 0x140000000);
            test(&a1, *(uintptr_t*)(scriptable + 0x40));

            auto b = *(uintptr_t*)(scriptable + 0x40);
            spdlog::debug("b: {:#x}", b);

            auto c = *(uintptr_t**)(scriptable + 0x40);
            spdlog::debug("c: {:#x}", (uintptr_t)c);
            spdlog::debug("a1: {:#x}", (uintptr_t)a1);

            REDString item;
            REDString amount;

            using REDString_t = void (*)(REDString* aThis, char* aText);
            RED4ext::REDfunc<REDString_t> REDString_ctor(0x1401B7830 - 0x140000000);

            REDString_ctor(&item, "Items.Jacket_03_old_04");
            REDString_ctor(&amount, "1");

            Unk523 args[4];
            args[0].unk0 = *(uintptr_t*)(0x1442FD030 - 0x140000000 + (uintptr_t)GetModuleHandle(nullptr));
            args[0].unk8 = (uint64_t)&a1;

            args[1].unk0 = (uintptr_t)(0x143C62438 - 0x140000000 + (uintptr_t)GetModuleHandle(nullptr));
            args[1].unk8 = (uint64_t)&item;

            args[2].unk0 = (uintptr_t)(0x143C62438 - 0x140000000 + (uintptr_t)GetModuleHandle(nullptr));
            args[2].unk8 = (uint64_t)&amount;

            CScriptableStackFrame stack;
            auto script40 = *(uintptr_t*)(scriptable + 0x40);
            auto script40100 = *(uintptr_t*)(script40 + 0x100);

            using ctor_t = CScriptableStackFrame* (*)(CScriptableStackFrame * aThis, __int64 aScriptable, Unk523* aArgs,
                                                      int aArgsCount, __int64 a5, __int64* a6);
            RED4ext::REDfunc<ctor_t> ctor(0x140270370 - 0x140000000);

            ctor(&stack, scriptable, args, 3, 0, 0);

            using exec_t = bool (*)(RED4ext::REDreverse::CBaseFunction * aThis, CScriptableStackFrame * stack);
            RED4ext::REDfunc<exec_t> exec(0x1402254A0 - 0x140000000);

            exec(func, &stack);
            auto a = 10;
        }
    }

    //{
    //    char byteCode[1]{};

    //    RED4ext::REDreverse::CStackFrame stack;
    //    stack.byteCode = byteCode;

    //    uint32_t time;
    //    RED4ext::ExecuteFunction("gameTimeSystem", "GetGameTime", stack, time);

    //    auto days = time / 0x15180;
    //    auto hours = (time % 0x15180 / 0x0E10);
    //    auto minutes = (time % 0x0E10 / 0x3C);
    //    auto seconds = (time % 0x3C);

    //    spdlog::debug(L"GetGameTime(): {} {}:{}:{}", days, hours, minutes, seconds);
    //
    //    static auto last = std::chrono::high_resolution_clock::now();
    //    auto now = std::chrono::high_resolution_clock::now();

    //    using namespace std::chrono_literals;

    //    // Every 1 minute, skip time by 6 hours, 5 minutes and 30 seconds.
    //    if ((now - last) > 1min)
    //    {
    //        char byteCode[] = {
    //            0x06, 0x00, 0x00, 0x00, 0x00,   // Int32Const hours + 6
    //            0x06, 0x00, 0x00, 0x00, 0x00,   // Int32Const minutes + 5
    //            0x06, 0x00, 0x00, 0x00, 0x00,   // Int32Const seconds + 30
    //            0x26,                           // ParamEnd
    //            0x00                            // Nop
    //        };

    //        *(int32_t*)(&byteCode[1]) = hours + 6;
    //        *(int32_t*)(&byteCode[6]) = minutes + 5;
    //        *(int32_t*)(&byteCode[11]) = seconds + 30;

    //        RED4ext::REDreverse::CStackFrame stack;
    //        stack.byteCode = byteCode;

    //        int32_t time;
    //        RED4ext::ExecuteFunction("gameTimeSystem", "SetGameTimeByHMS", stack, time);

    //        last = now;
    //    }
    //}
}

RED4EXT_EXPORT void OnShutdown()
{
    auto app = RED4ext::Playground::App::Get();
    app->Shutdown();
}
