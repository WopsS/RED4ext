#include "stdafx.hpp"
#include "Api.hpp"
#include "App.hpp"
#include "Utils.hpp"

#include "RED4ext/Version.hpp"

const RED4ext::v1::VersionInfo* v1::GetSDKVersion()
{
    static RED4ext::v1::VersionInfo version = RED4ext::v1::CreateVersion(
        RED4EXT_VER_MAJOR, RED4EXT_VER_MINOR, RED4EXT_VER_PATCH, RED4EXT_V1_PRERELEASE_TYPE_NONE, 0);

    return &version;
}

const RED4ext::v1::VersionInfo* v1::GetRuntimeVersion()
{
    static RED4ext::v1::VersionInfo version;
    static std::once_flag once;
    std::call_once(once, []() {
        auto app = App::Get();
        auto filename = app->GetExecutablePath();

        auto size = GetFileVersionInfoSize(filename.c_str(), nullptr);
        if (!size)
        {
            auto err = GetLastError();
            auto errMsg = Utils::FormatErrorMessage(err);
            spdlog::error(L"Could not retrive game's version size, error: 0x{:X}, description: {}", err, errMsg);

            return;
        }

        auto data = _malloca(size);
        if (!data)
        {
            spdlog::error(L"Could not allocate {} bytes on stack or heap", size);
            return;
        }

        if (!GetFileVersionInfo(filename.c_str(), 0, size, data))
        {
            auto err = GetLastError();
            auto errMsg = Utils::FormatErrorMessage(err);
            spdlog::error(L"Could not retrive game's version info, error: 0x{:X}, description: {}", err, errMsg);

            _freea(data);
            return;
        }

        VS_FIXEDFILEINFO* buffer = nullptr;
        uint32_t length = 0;

        if (!VerQueryValue(data, L"\\", reinterpret_cast<LPVOID*>(&buffer), &length) || !length)
        {
            auto err = GetLastError();
            auto errMsg = Utils::FormatErrorMessage(err);
            spdlog::error(L"Could not query version info, error: 0x{:X}, description: {}", err, errMsg);

            _freea(data);
            return;
        }

        if (buffer->dwSignature != 0xFEEF04BD)
        {
            spdlog::error(L"Retrived version signature does not match");
            _freea(data);

            return;
        }

        uint8_t major = (buffer->dwProductVersionMS >> 16) & 0xFF;
        uint16_t minor = buffer->dwProductVersionMS & 0xFFFF;
        uint32_t patch = (buffer->dwProductVersionLS >> 16) & 0xFFFF;

        version = RED4EXT_V1_SEMVER(major, minor, patch);

        _freea(data);
    });

    return &version;
}
