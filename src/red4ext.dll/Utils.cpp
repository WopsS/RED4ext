#include "stdafx.hpp"
#include "Utils.hpp"
#include "Config.hpp"
#include "DevConsole.hpp"
#include "Paths.hpp"

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

void Utils::CreateLogger(const Paths& aPaths, const Config& aConfig, const DevConsole& aDevConsole)
{
    try
    {
        auto dir = aPaths.GetLogsDir();

        std::error_code err;
        auto exists = std::filesystem::exists(dir, err);
        if (err)
        {
            auto errVal = err.value();
            const auto& category = err.category();
            auto msg = category.message(errVal);

            SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE(
                L"An error occured while checking logs directory existence:\n{}\n\nDirectory: {}", Utils::Widen(msg),
                dir);

            return;
        }

        if (!exists)
        {
            std::filesystem::create_directories(dir, err);
            if (err)
            {
                auto errVal = err.value();
                const auto& category = err.category();
                auto msg = category.message(errVal);

                SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE(
                    L"An error occured while creating the logs directory:\n{}\n\nDirectory: {}", Utils::Widen(msg),
                    dir);

                return;
            }
        }

        constexpr auto oneByte = 1;
        constexpr auto oneKbInB = 1024 * oneByte;
        constexpr auto oneMbInB = 1024 * oneKbInB;
        constexpr auto tenMbInB = 10 * oneMbInB;

        constexpr size_t maxFileSize = tenMbInB;
        constexpr size_t maxFiles = 5;

        auto file = dir / L"game.log";
        auto logger = spdlog::rotating_logger_mt("", file, maxFileSize, maxFiles, true);
        logger->set_level(aConfig.GetLogLevel());
        logger->flush_on(aConfig.GetFlushLevel());

        if (aConfig.HasDevConsole() && aDevConsole.IsOutputRedirected())
        {
            auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            logger->sinks().push_back(consoleSink);
        }

        spdlog::set_default_logger(logger);
    }
    catch (const std::exception& e)
    {
        SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE(L"An exception occured while creating the logger:\n{}",
                                            Utils::Widen(e.what()));
    }
}

std::wstring Utils::FormatSystemMessage(uint32_t aMessageId)
{
    wil::unique_hlocal_ptr<wchar_t> buffer;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr,
                  aMessageId, LANG_USER_DEFAULT, wil::out_param_ptr<LPWSTR>(buffer), 0, nullptr);

    return buffer.get();
}

int32_t Utils::ShowMessageBoxEx(const std::wstring_view aCaption, const std::wstring_view aText, uint32_t aType)
{
    return MessageBox(nullptr, aText.data(), aCaption.data(), aType);
}

int32_t Utils::ShowMessageBox(const std::wstring_view aText, uint32_t aType)
{
    return ShowMessageBoxEx(L"RED4ext", aText, aType);
}

std::wstring Utils::Widen(const std::string_view aText)
{
    if (aText.empty())
    {
        return L"";
    }

    std::wstring result;

    auto len = MultiByteToWideChar(CP_UTF8, 0, aText.data(), static_cast<int32_t>(aText.size()), nullptr, 0);
    if (len)
    {
        result.resize(len);
        len = MultiByteToWideChar(CP_UTF8, 0, aText.data(), static_cast<int32_t>(aText.size()), result.data(),
                                  static_cast<int32_t>(result.size()));
    }

    // Second pass.
    if (len <= 0)
    {
        result = fmt::format(L"Failed to convert narrow to wide string, last error is {}", GetLastError());
    }

    return result;
}
