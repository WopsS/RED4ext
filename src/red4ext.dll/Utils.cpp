#include "stdafx.hpp"
#include "Utils.hpp"

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
