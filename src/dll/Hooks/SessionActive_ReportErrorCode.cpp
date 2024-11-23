#include "SessionActive_ReportErrorCode.hpp"
#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
#include "stdafx.hpp"

namespace
{
bool isAttached = false;

void _GsmState_SessionActive_ReportErrorCode(uintptr_t);
Hook<decltype(&_GsmState_SessionActive_ReportErrorCode)> State_SessionActive_ReportErrorCode(
    0x7FA31576, &_GsmState_SessionActive_ReportErrorCode);

void _GsmState_SessionActive_ReportErrorCode(uintptr_t aThis)
{
    auto errorCode = *reinterpret_cast<uint32_t*>(aThis + 0x88u);

    if (errorCode > 0u)
    {
        static const auto type = RED4ext::CRTTISystem::Get()->GetEnum("gsmStateError");

        spdlog::error("=======");
        spdlog::error("A game session error occurred. Error code: {} ({}).", type->hashList[errorCode].ToString(),
                      errorCode);
        spdlog::error("=======");
    }

    return State_SessionActive_ReportErrorCode(aThis);
}
} // namespace

bool Hooks::SessionActive_ReportErrorCode::Attach()
{
    spdlog::trace("Trying to attach the hook for the game session error code reporter at {:#x}...",
                  State_SessionActive_ReportErrorCode.GetAddress());

    auto result = State_SessionActive_ReportErrorCode.Attach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not attach the hook for the game session error code reporter. Detour error code: {}",
                      result);
    }
    else
    {
        spdlog::trace("The hook for the game session error code reporter was attached");
    }

    isAttached = result == NO_ERROR;
    return isAttached;
}

bool Hooks::SessionActive_ReportErrorCode::Detach()
{
    if (!isAttached)
    {
        return false;
    }

    spdlog::trace("Trying to detach the hook for the game session error code reporter at {:#x}...",
                  State_SessionActive_ReportErrorCode.GetAddress());

    auto result = State_SessionActive_ReportErrorCode.Detach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not detach the hook for the game session error code reporter. Detour error code: {}",
                      result);
    }
    else
    {
        spdlog::trace("The hook for the game session error code reporter was detached");
    }

    isAttached = result != NO_ERROR;
    return !isAttached;
}
