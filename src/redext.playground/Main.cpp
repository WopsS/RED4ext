#include <stdafx.hpp>
#include <REDext/REDext.hpp>

#include <App.hpp>
#include <REDs/REDfunc.hpp>
#include <REDs/REDptr.hpp>

struct CRTTIType
{
    uintptr_t __vftable;
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

    {
        // Ugly, seems like other functions use a different holder.
        REDptr<uintptr_t**> funcHolder(0x143C90770 - 0x140000000);

        // ScriptGameInstance
        uint64_t nameHash = 0xBB1F04F0666AEAF3;
        auto rttiType = rtti->GetClass(nameHash);

        // GetFrameNumber
        nameHash = 0x475DAE45D7EC50CD;
        auto registrationIndex = *(int32_t*)(GetFunction(rttiType, nameHash) + 0x88);

        using GetFrameNumber_t = int64_t (*)(int64_t aScriptable, char** aStackFrame, uintptr_t* aOut, int64_t a4);
        GetFrameNumber_t GetFrameNumber = reinterpret_cast<GetFrameNumber_t>((*funcHolder)[registrationIndex]);

        // Ugly, find a better way to handle this, needs more RE.
        char stack[0x100]{};
        char* a[0x100]{};
        a[0] = &stack[0];

        size_t frame;

        // First parameter is incorrect, should be IScriptable. Needs to find how to get it from CRTTIType.
        GetFrameNumber(0, a, &frame, 0);
        spdlog::debug(L"GetFrameNumber(): {}", frame);
    }
}

REDEXT_EXPORT void OnShutdown()
{
    auto app = App::Get();
    app->Shutdown();
}
