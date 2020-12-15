#include <stdafx.hpp>
#include <REDext/REDext.hpp>

#include <App.hpp>
#include <REDs/REDfunc.hpp>
#include <REDs/REDptr.hpp>

struct CRTTIType
{
    virtual void dtor(uint8_t aFlags) = 0;
    virtual void GetName(uint64_t* aOut) = 0;
};

struct CRTTI
{
    virtual void sub_0() = 0;
    virtual void sub_8() = 0;
    virtual CRTTIType* GetClass(uint64_t aName) = 0;
};

using namespace REDext::Playground;
REDfunc<CRTTI* (*)()> RTTI_Get(0x14020C860 - 0x140000000);
REDfunc<char* (*)(uint64_t& aHash)> CNamePool_Get(0x1401BC900 - 0x140000000);

struct CGameEngine
{
    struct Unk
    {
        struct Unk2
        {
            virtual void sub_0() = 0;
            virtual uintptr_t sub_8(uintptr_t a1) = 0;
        };

        int8_t unk[0x10];
        Unk2* unk10;
    };

    static_assert(offsetof(Unk, unk10) == 0x10);

    int8_t unk[0x260];
    Unk* unk260;
};

static_assert(offsetof(CGameEngine, unk260) == 0x260);

REDptr<CGameEngine**> gameEngine(0x1440689D8 - 0x140000000);

REDEXT_EXPORT void OnBaseInitialization()
{
    auto app = App::Get();
    app->Init();
}

REDEXT_EXPORT void OnInitialization()
{
}

REDEXT_EXPORT void OnUpdate()
{
    auto app = App::Get();
    app->Run();

    auto rtti = RTTI_Get();

    // This only works for GOG 1.04.

    using GetFunction_t = uintptr_t (*)(CRTTIType* aClass, uint64_t aName);
    static REDfunc<GetFunction_t> GetFunction(0x1402135F0 - 0x140000000);

    //{
    //    // Ugly, seems like other functions use a different holder.
    //    REDptr<uintptr_t**> funcHolder(0x143C90770 - 0x140000000);

    //    // ScriptGameInstance
    //    uint64_t nameHash = 0xBB1F04F0666AEAF3;
    //    auto rttiType = rtti->GetClass(nameHash);

    //    // GetFrameNumber
    //    nameHash = 0x475DAE45D7EC50CD;
    //    auto registrationIndex = *(int32_t*)(GetFunction(rttiType, nameHash) + 0x88);

    //    using GetFrameNumber_t = int64_t (*)(int64_t aScriptable, char** aStackFrame, uintptr_t* aOut, int64_t a4);
    //    GetFrameNumber_t GetFrameNumber = reinterpret_cast<GetFrameNumber_t>((*funcHolder)[registrationIndex]);

    //    // Ugly, find a better way to handle this, needs more RE.
    //    char stack[0x100]{};
    //    char* a[0x100]{};
    //    a[0] = &stack[0];

    //    size_t frame;

    //    // First parameter is incorrect, should be IScriptable. Needs to find how to get it from CRTTIType.
    //    GetFrameNumber(0, a, &frame, 0);
    //    //spdlog::debug(L"GetFrameNumber(): {}", frame);
    //}
    {
        // Ugly, seems like other functions use a different holder.
        REDptr<uintptr_t**> funcHolder(0x143C70770 - 0x140000000);

        // gameTimeSystem
        uint64_t nameHash = 0x72161A4711B288B7;
        auto rttiType = rtti->GetClass(nameHash);

        // GetGameTime
        nameHash = 0x355A7BA6A3FBBDDC;
        auto registrationIndex = *(int32_t*)(GetFunction(rttiType, nameHash) + 0x88);

        using GetGameTime_t = int64_t (*)(uintptr_t aScriptable, char** aStackFrame, int32_t* aOut, int64_t a4);
        GetGameTime_t GetGameTime = reinterpret_cast<GetGameTime_t>((*funcHolder)[registrationIndex]);

        auto handle = GetModuleHandle(nullptr);

        using sub_1413E2A00_t = uint64_t (*)();
        static REDfunc<sub_1413E2A00_t> sub_1413E2A00(0x1413E2A00 - 0x140000000);

        auto engine = gameEngine.GetPtr();
        auto unk10 = (*engine)->unk260->unk10;

        // I think we should increment some ref here, but didn't really check into it.
        auto scriptable = unk10->sub_8(sub_1413E2A00());

        // Ugly, find a better way to handle this, needs more RE.
        char stack[0x100]{};
        char* a[0x100]{};
        a[0] = &stack[0];

        int32_t time;

        GetGameTime(scriptable, a, &time, 0);
        spdlog::debug(L"GetGameTime(): {} {}:{}:{}", time / 0x15180, (time % 0x15180 / 0x0E10), (time % 0x0E10 / 0x3C),
                      (time % 0x3C));
    }
}

REDEXT_EXPORT void OnShutdown()
{
    auto app = App::Get();
    app->Shutdown();
}
