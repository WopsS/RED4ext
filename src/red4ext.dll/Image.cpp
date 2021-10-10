#include "stdafx.hpp"
#include "Image.hpp"
#include "Utils.hpp"

Image::Image()
    : m_isCyberpunk(false)
    , m_version(RED4EXT_V0_SEMVER(0, 0, 0))
{
    std::wstring fileName;
    auto hr = wil::GetModuleFileNameW(nullptr, fileName);
    if (FAILED(hr))
    {
        SHOW_LAST_ERROR_MESSAGE_FILE_LINE(L"Could not get executable's file name.");
        return;
    }

    auto size = GetFileVersionInfoSize(fileName.c_str(), nullptr);
    if (!size)
    {
        if (GetLastError() != ERROR_RESOURCE_TYPE_NOT_FOUND)
        {
            SHOW_LAST_ERROR_MESSAGE_FILE_LINE(L"Could not retrieve version info size.\n\nFile name: {}", fileName);
        }
        
        // Else, fail silently, executables might not have the version information.
        return;
    }

    std::unique_ptr<uint8_t[]> data(new (std::nothrow) uint8_t[size]());
    if (!data)
    {
        SHOW_MESSAGE_BOX_FILE_LINE(MB_ICONERROR | MB_OK, L"Could not allocate {} byte(s).\n\nFile name: {}", size,
                                   fileName);
        return;
    }

    if (!GetFileVersionInfo(fileName.c_str(), 0, size, data.get()))
    {
        SHOW_LAST_ERROR_MESSAGE_FILE_LINE(L"Could not retrieve version info.\n\nFile name: {}", fileName);
        return;
    }

    struct LangAndCodePage
    {
        WORD language;
        WORD codePage;
    } * translations;
    uint32_t translationsBytes;

    if (!VerQueryValue(data.get(), L"\\VarFileInfo\\Translation", reinterpret_cast<void**>(&translations),
                       &translationsBytes))
    {
        SHOW_LAST_ERROR_MESSAGE_FILE_LINE(L"Could not retrieve translations.\n\nFile name: {}", fileName);
        return;
    }

    for (uint32_t i = 0; i < (translationsBytes / sizeof(LangAndCodePage)); i++)
    {
        wchar_t* productName;
        auto subBlock = fmt::format(L"\\StringFileInfo\\{:04x}{:04x}\\ProductName", translations[i].language,
                                    translations[i].codePage);

        if (VerQueryValue(data.get(), subBlock.c_str(), reinterpret_cast<void**>(&productName), &translationsBytes))
        {
            constexpr std::wstring_view expectedProductName = L"Cyberpunk 2077";
            if (productName == expectedProductName)
            {
                m_isCyberpunk = true;
                break;
            }
        }
    }

    if (m_isCyberpunk)
    {
        VS_FIXEDFILEINFO* fileInfo;
        UINT fileInfoBytes;

        if (!VerQueryValue(data.get(), L"\\", reinterpret_cast<LPVOID*>(&fileInfo), &fileInfoBytes))
        {
            SHOW_LAST_ERROR_MESSAGE_FILE_LINE(L"Could not retrieve the file's info.\n\nFile name: {}", fileName);
            return;
        }

        constexpr auto signature = 0xFEEF04BD;
        if (fileInfo->dwSignature != signature)
        {
            SHOW_LAST_ERROR_MESSAGE_FILE_LINE(
                L"The file's signature ({:#x}) did not match the expected value ({:#x}).\n\nFile name: {}",
                fileInfo->dwSignature, signature, fileName);
            return;
        }

        uint8_t major = (fileInfo->dwProductVersionMS >> 16) & 0xFF;
        uint16_t minor = fileInfo->dwProductVersionMS & 0xFFFF;
        uint32_t patch = (fileInfo->dwProductVersionLS >> 16) & 0xFFFF;

        m_version = RED4EXT_SEMVER(major, minor, patch);
    }
}

Image* Image::Get()
{
    static Image instance;
    return &instance;
}

bool Image::IsCyberpunk() const
{
    return m_isCyberpunk;
}

bool Image::IsSupported() const
{
    return m_version == GetSupportedVersion();
}

const RED4ext::VersionInfo& Image::GetVersion() const
{
    return m_version;
}

const RED4ext::VersionInfo Image::GetSupportedVersion() const
{
    return RED4EXT_RUNTIME_LATEST;
}
