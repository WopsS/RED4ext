#pragma once

namespace RED4ext::Registry
{
    enum class Key : uint8_t
    {
        CurrentConfig,
        CurrentUser,
        ClassesRoot,
        LocalMachine,
        Users
    };

    template<typename T, typename... Args>
    std::enable_if_t<!std::conjunction_v<std::is_constructible<std::wstring, Args>...> &&
                       !std::conjunction_v<std::is_constructible<std::wstring_view, Args>...>,
                     T>
    Read(Key aKey, Args&&... aKeys)
    {
        static_assert(false, "Arguments must be of type std::wstring");
    }

    template<typename T, typename... Args>
    std::enable_if_t<(std::is_integral_v<T> || std::is_same_v<T, std::wstring>) && (
                       std::conjunction_v<std::is_constructible<std::wstring, Args>...> ||
                       std::conjunction_v<std::is_constructible<std::wstring_view, Args>...>),
                     T>
    Read(Key aKey, Args&&... aKeys)
    {
        T result{};

        HKEY key;

        std::filesystem::path regPath;

        // Doing this here, it is easier to get the subkeys and the value here.
        regPath = (regPath / ... / aKeys);

        auto subKey = regPath.parent_path();
        auto value = regPath.filename();

        switch (aKey)
        {
        case Key::ClassesRoot:
        {
            key = HKEY_CLASSES_ROOT;
            regPath = L"HKEY_CLASSES_ROOT" / regPath;

            break;
        }
        case Key::CurrentConfig:
        {
            key = HKEY_CURRENT_CONFIG;
            regPath = L"HKEY_CURRENT_CONFIG" / regPath;

            break;
        }
        case Key::CurrentUser:
        {
            key = HKEY_CURRENT_USER;
            regPath = L"HKEY_CURRENT_USER" / regPath;

            break;
        }
        case Key::LocalMachine:
        {
            key = HKEY_LOCAL_MACHINE;
            regPath = L"HKEY_LOCAL_MACHINE" / regPath;

            break;
        }
        case Key::Users:
        {
            key = HKEY_USERS;
            regPath = L"HKEY_USERS" / regPath;

            break;
        }
        }

        uint32_t err = ERROR_SUCCESS;
        uint32_t size = sizeof(T);

        if constexpr (std::is_same_v<T, std::wstring>)
        {
            // Get the string size.
            err = RegGetValue(key, subKey.c_str(), value.c_str(), RRF_RT_REG_SZ, nullptr, nullptr,
                              reinterpret_cast<LPDWORD>(&size));
            if (err == ERROR_SUCCESS)
            {
                // Calculate the real size of the string and exclude the NULL written by the Win32 API.
                result.resize(size / sizeof(wchar_t) - sizeof(wchar_t));
                err = RegGetValue(key, subKey.c_str(), value.c_str(), RRF_RT_REG_SZ, nullptr, &result[0],
                                  reinterpret_cast<LPDWORD>(&size));
            }
        }
        else
        {
            err = RegGetValue(key, subKey.c_str(), value.c_str(), RRF_RT_REG_DWORD | RRF_RT_REG_QWORD, nullptr, &result,
                              reinterpret_cast<LPDWORD>(&size));
        }

        if (err != ERROR_SUCCESS)
        {
            spdlog::error(L"An error ({:#x}) occured while reading registry value '{}' from '{}'", err, value.wstring(),
                          regPath.parent_path().wstring());
        }

        return result;
    }
}
