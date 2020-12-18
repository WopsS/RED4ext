#pragma once

#include <cstdint>
#include <string_view>

#include <RED4ext/REDhash.hpp>
#include <RED4ext/REDreverse/CStackFrame.hpp>
#include <RED4ext/REDreverse/Function.hpp>
#include <RED4ext/REDreverse/GameEngine.hpp>
#include <RED4ext/REDreverse/RTTI/CClass.hpp>
#include <RED4ext/REDreverse/RTTI/RTTISystem.hpp>

namespace RED4ext
{
    template<typename T>
    void ExecuteFunction(std::string_view aClass, std::string_view aName, RED4ext::REDreverse::CStackFrame& aStack,
                         T& aOut, int64_t a4 = 0)
    {
        auto rtti = RED4ext::REDreverse::CRTTISystem::Get();
        auto type = rtti->GetType<RED4ext::REDreverse::CClass*>(RED4ext::FNV1a(aClass));
        if (!type)
        {
            return;
        }

        auto func = type->GetFunction(RED4ext::FNV1a(aName));
        if (!func)
        {
            return;
        }

        auto engine = RED4ext::REDreverse::CGameEngine::Get();
        auto unk10 = engine->framework->unk10;

        // I think we should increment some ref here, but didn't really check into it.
        auto scriptable = unk10->GetTypeInstance(type);
        aStack.scriptable = scriptable;

        func->Call(scriptable, aStack, aOut, a4);
    }
}
