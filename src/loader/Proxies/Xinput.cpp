#include "Xinput.hpp"

using XInputGetState_t = decltype(&XInputGetState);
using XInputSetState_t = decltype(&XInputSetState);
using XInputGetCapabilities_t = decltype(&XInputGetCapabilities);
using XInputGetDSoundAudioDeviceGuids_t = decltype(&XInputGetDSoundAudioDeviceGuids);

namespace Functions
{
XInputGetState_t XInputGetState;
XInputSetState_t XInputSetState;
XInputGetCapabilities_t XInputGetCapabilities;
XInputGetDSoundAudioDeviceGuids_t XInputGetDSoundAudioDeviceGuids;
} // namespace Functions

DWORD WINAPI _XInputGetState(DWORD dwUserIndex, XINPUT_STATE* pState)
{
    return Functions::XInputGetState(dwUserIndex, pState);
}

DWORD WINAPI _XInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration)
{
    return Functions::XInputSetState(dwUserIndex, pVibration);
}

DWORD WINAPI _XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities)
{
    return Functions::XInputGetCapabilities(dwUserIndex, dwFlags, pCapabilities);
}

DWORD WINAPI _XInputGetDSoundAudioDeviceGuids(DWORD dwUserIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid)
{
    return Functions::XInputGetDSoundAudioDeviceGuids(dwUserIndex, pDSoundRenderGuid, pDSoundCaptureGuid);
}

bool Xinput::LoadOriginal()
{
    wil::unique_cotaskmem_string rawPath;
    if (FAILED(SHGetKnownFolderPath(FOLDERID_System, KF_FLAG_DEFAULT, nullptr, &rawPath)))
    {
        return false;
    }

    constexpr auto dllName = "XInput9_1_0.dll";

    std::filesystem::path dll = rawPath.get();
    dll /= dllName;

    auto handle = LoadLibrary(dll.c_str());
    if (!handle)
    {
        return false;
    }

    Functions::XInputGetState = reinterpret_cast<XInputGetState_t>(GetProcAddress(handle, "XInputGetState"));
    Functions::XInputSetState = reinterpret_cast<XInputSetState_t>(GetProcAddress(handle, "XInputSetState"));
    Functions::XInputGetCapabilities =
        reinterpret_cast<XInputGetCapabilities_t>(GetProcAddress(handle, "XInputGetCapabilities"));
    Functions::XInputGetDSoundAudioDeviceGuids =
        reinterpret_cast<XInputGetDSoundAudioDeviceGuids_t>(GetProcAddress(handle, "XInputGetDSoundAudioDeviceGuids"));

    return true;
}
