#include <stdafx.hpp>
#include <Launchers/CustomLauncher.hpp>

RED4ext::Launchers::CustomLauncher::CustomLauncher()
{
}

const std::wstring RED4ext::Launchers::CustomLauncher::GetName() const
{
    return L"Custom Launcher";
}

const bool RED4ext::Launchers::CustomLauncher::IsInstalled() const
{
    return true;
}

const bool RED4ext::Launchers::CustomLauncher::IsRunning() const
{
    return true;
}

const bool RED4ext::Launchers::CustomLauncher::Launch() const
{
    return false;
}

RED4ext::Launchers::BaseLauncher::GameInfo RED4ext::Launchers::CustomLauncher::GetGameInfo()
{
    auto path = GetGamePath();

    BaseLauncher::GameInfo result;
    result.RootDir = path / L"bin" / L"x64";
    result.ExePath = result.RootDir / "Cyberpunk2077.exe";

    return result;
}

std::filesystem::path RED4ext::Launchers::CustomLauncher::GetGamePath()
{
    std::filesystem::path result;

    // https://docs.microsoft.com/en-us/windows/win32/learnwin32/example--the-open-dialog-box.
    auto hresult = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hresult))
    {
        IFileOpenDialog* dialog = nullptr;

        hresult = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog,
                                   reinterpret_cast<void**>(&dialog));

        if (SUCCEEDED(hresult))
        {
            dialog->SetTitle(L"Choose the game directory");
            dialog->SetOptions(FOS_PICKFOLDERS);

            hresult = dialog->Show(nullptr);

            if (SUCCEEDED(hresult))
            {
                IShellItem* item;

                hresult = dialog->GetResult(&item);
                if (SUCCEEDED(hresult))
                {
                    wchar_t* path;
                    hresult = item->GetDisplayName(SIGDN_FILESYSPATH, &path);

                    if (SUCCEEDED(hresult))
                    {
                        result = path;
                        CoTaskMemFree(path);
                    }

                    item->Release();
                }
            }

            dialog->Release();
        }

        CoUninitialize();
    }

    spdlog::info(L"'{}' will be used as the game directory", result.wstring());
    return result;
}
