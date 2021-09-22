#pragma once

class Config;
class DevConsole;
class Paths;

namespace Utils
{
void CreateLogger(const Paths& aPaths, const Config& aConfig, const DevConsole& aDevConsole);

std::wstring FormatSystemMessage(uint32_t aMessageId);

int32_t ShowMessageBoxEx(const std::wstring_view aCaption, const std::wstring_view aText, uint32_t aType = MB_OK);
int32_t ShowMessageBox(const std::wstring_view aText, uint32_t aType = MB_OK);

std::wstring Widen(const std::string_view aText);

template<typename... Args>
int32_t ShowMessageBox(uint32_t aType, const std::wstring_view aText, Args&&... aArgs)
{
    return ShowMessageBox(fmt::format(aText, std::forward<Args>(aArgs)...), aType);
}

template<typename... Args>
void ShowLastErrorMessage(uint32_t aType, const std::wstring_view aAdditionalText = "", Args&&... aArgs)
{
    auto errorCode = GetLastError();
    auto caption = fmt::format(L"RED4ext (error {})", errorCode);
    auto msg = FormatSystemMessage(errorCode);

    if (!aAdditionalText.empty())
    {
        msg += L"\n";
        msg += aAdditionalText;

        if constexpr (sizeof...(Args) > 0)
        {
            msg = fmt::format(msg, std::forward<Args>(aArgs)...);
        }
    }

    ShowMessageBoxEx(caption.c_str(), msg.c_str(), aType);
}
} // namespace Utils

template<typename Char>
struct fmt::formatter<std::filesystem::path, Char> : formatter<basic_string_view<Char>, Char>
{
    template<typename FormatContext>
    auto format(const std::filesystem::path& path, FormatContext& ctx)
    {
        return formatter<basic_string_view<Char>, Char>::format(path.c_str(), ctx);
    }
};

#ifndef SHOW_LAST_ERROR_MESSAGE_FILE_LINE
#define SHOW_LAST_ERROR_MESSAGE_FILE_LINE(additionalText, ...)                                                         \
    Utils::ShowLastErrorMessage(MB_ICONWARNING | MB_OK, additionalText L"\n\n{}:{}", __VA_ARGS__, TEXT(__FILE__),      \
                                __LINE__)
#endif

#ifndef SHOW_LAST_ERROR_MESSAGE_AND_EXIT_FILE_LINE
#define SHOW_LAST_ERROR_MESSAGE_AND_EXIT_FILE_LINE(additionalText, ...)                                                \
    Utils::ShowLastErrorMessage(                                                                                       \
        MB_ICONERROR | MB_OK, additionalText L"\n\n{}:{}\n\nThe game will close now to prevent unexpected behavior.",  \
        __VA_ARGS__, TEXT(__FILE__), __LINE__);                                                                        \
    TerminateProcess(GetCurrentProcess(), 1)
#endif

#ifndef SHOW_MESSAGE_BOX_FILE_LINE
#define SHOW_MESSAGE_BOX_FILE_LINE(type, msg, ...)                                                                     \
    Utils::ShowMessageBox(type, msg L"\n\n{}:{}", __VA_ARGS__, TEXT(__FILE__), __LINE__)
#endif

#ifndef SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE
#define SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE(msg, ...)                                                                  \
    Utils::ShowMessageBox(MB_ICONERROR | MB_OK,                                                                        \
                          msg L"\n\n{}:{}\n\nThe game will close now to prevent unexpected behavior.", __VA_ARGS__,    \
                          TEXT(__FILE__), __LINE__);                                                                   \
    TerminateProcess(GetCurrentProcess(), 1)
#endif
