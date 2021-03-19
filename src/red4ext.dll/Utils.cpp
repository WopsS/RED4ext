#include "stdafx.hpp"
#include "Utils.hpp"
#include "App.hpp"

std::wstring Utils::FormatErrorMessage(uint32_t aErrorCode)
{
    wchar_t* buffer = nullptr;
    auto errorCode = GetLastError();

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr,
                  errorCode, LANG_USER_DEFAULT, reinterpret_cast<LPWSTR>(&buffer), 0, nullptr);

    std::wstring result = buffer;

    LocalFree(buffer);
    buffer = nullptr;

    return result;
}

const RED4ext::VersionInfo Utils::GetRuntimeVersion()
{
    auto app = App::Get();
    auto filename = app->GetExecutablePath();

    auto size = GetFileVersionInfoSize(filename.c_str(), nullptr);
    if (!size)
    {
        auto err = GetLastError();
        auto errMsg = Utils::FormatErrorMessage(err);
        spdlog::error(L"Could not retrive game's version size, error: 0x{:X}, description: {}", err, errMsg);

        return RED4EXT_SEMVER(0, 0, 0);
    }

    auto data = new char[size];
    if (!data)
    {
        spdlog::error(L"Could not allocate {} bytes on stack or heap", size);
        return RED4EXT_SEMVER(0, 0, 0);
    }

    if (!GetFileVersionInfo(filename.c_str(), 0, size, data))
    {
        auto err = GetLastError();
        auto errMsg = Utils::FormatErrorMessage(err);
        spdlog::error(L"Could not retrive game's version info, error: 0x{:X}, description: {}", err, errMsg);

        delete[] data;
        return RED4EXT_SEMVER(0, 0, 0);
    }

    VS_FIXEDFILEINFO* buffer = nullptr;
    uint32_t length = 0;

    if (!VerQueryValue(data, L"\\", reinterpret_cast<LPVOID*>(&buffer), &length) || !length)
    {
        auto err = GetLastError();
        auto errMsg = Utils::FormatErrorMessage(err);
        spdlog::error(L"Could not query version info, error: 0x{:X}, description: {}", err, errMsg);

        delete[] data;
        return RED4EXT_SEMVER(0, 0, 0);
    }

    if (buffer->dwSignature != 0xFEEF04BD)
    {
        spdlog::error(L"Retrived version signature does not match");
        delete[] data;

        return RED4EXT_SEMVER(0, 0, 0);
    }

    uint8_t major = (buffer->dwProductVersionMS >> 16) & 0xFF;
    uint16_t minor = buffer->dwProductVersionMS & 0xFFFF;
    uint32_t patch = (buffer->dwProductVersionLS >> 16) & 0xFFFF;

    delete[] data;
    return RED4EXT_SEMVER(major, minor, patch);
}
