#pragma once

#include <array>
#include <cstdint>
#include <sstream>
#include <string_view>
#include <type_traits>
#include <vector>

#include <malloc.h>
#include <stdlib.h>

#include <RED4ext/RED4ext.hpp>
#include <RED4ext/REDhash.hpp>
#include <RED4ext/REDreverse/Function.hpp>
#include <RED4ext/REDreverse/GameEngine.hpp>
#include <RED4ext/REDreverse/RTTI/CClass.hpp>
#include <RED4ext/REDreverse/RTTI/RTTISystem.hpp>
#include <RED4ext/REDreverse/Scripting/StackFrame.hpp>

namespace RED4ext
{
    template<typename T, typename... Args>
    std::enable_if_t<std::is_pointer_v<T> || std::is_same_v<T, std::nullptr_t>, bool> ExecuteFunction(
      REDreverse::Scripting::IScriptable* aScriptable, REDreverse::CBaseFunction* aFunc, T aOut, Args&&... aArgs)
    {
        using CStackType = REDreverse::CScriptableStackFrame::CStackType;
        std::array<CStackType, sizeof...(aArgs)> args;

        if (args.size() && aFunc->params.size)
        {
            size_t i = 0;
            ((args[i].type = *(REDreverse::CRTTIBaseType**)aFunc->params.unk0[i], args[i++].value = &aArgs), ...);
        }

        CStackType result;
        if (aOut)
        {
            result.value = aOut;
        }

        auto ptr = _malloca(sizeof(REDreverse::CScriptableStackFrame));
        auto stack = static_cast<REDreverse::CScriptableStackFrame*>(ptr);

        REDreverse::CScriptableStackFrame::Construct(stack, aScriptable, args.data(),
                                                     static_cast<uint32_t>(args.size()), aOut ? &result : nullptr, 0);
        auto success = aFunc->Call(stack);

        _freea(ptr);
        return success;
    }

    template<typename T, typename... Args>
    std::enable_if_t<std::is_pointer_v<T> || std::is_same_v<T, std::nullptr_t>, bool> ExecuteFunction(
      std::string_view aClass, std::string_view aFunc, T aOut, Args&&... aArgs)
    {
        auto rtti = RED4ext::REDreverse::CRTTISystem::Get();
        auto type = rtti->GetType<RED4ext::REDreverse::CClass*>(RED4ext::FNV1a(aClass));
        if (!type)
        {
            std::stringstream message;
            message << "Class '" << aClass << "' not found";

            Log::Error("RED4ext.SDK", message.str().c_str());
            return false;
        }

        auto func = type->GetFunction(RED4ext::FNV1a(aFunc));
        if (!func)
        {
            std::stringstream message;
            message << "Function '" << aClass << "::" << aFunc << "' not found";

            Log::Error("RED4ext.SDK", message.str().c_str());
            return false;
        }

        auto engine = RED4ext::REDreverse::CGameEngine::Get();
        auto unk10 = engine->framework->unk10;

        // I think we should increment some ref here, but didn't really check into it.
        auto scriptable = unk10->GetTypeInstance(type);

        return ExecuteFunction(scriptable, func, aOut, std::forward<Args>(aArgs)...);
    }
}
