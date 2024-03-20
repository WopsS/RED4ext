#include "App.hpp"
#include "Image.hpp"
#include "Utils.hpp"

BOOL APIENTRY DllMain(HMODULE aModule, DWORD aReason, LPVOID aReserved)
{
    RED4EXT_UNUSED_PARAMETER(aReserved);

    switch (aReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(aModule);

        try
        {
            const auto image = Image::Get();
            if (!image->IsCyberpunk())
            {
                break;
            }

            App::Construct();
        }
        catch (const std::exception& e)
        {
            SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE("An exception occured while loading RED4ext.\n\n{}",
                                                Utils::Widen(e.what()));
        }
        catch (...)
        {
            SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE("An unknown exception occured while loading RED4ext.");
        }

        break;
    }
    case DLL_PROCESS_DETACH:
    {
        try
        {
            const auto image = Image::Get();
            if (!image->IsCyberpunk())
            {
                break;
            }

            App::Destruct();
        }
        catch (const std::exception& e)
        {
            SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE("An exception occured while unloading RED4ext.\n\n{}",
                                                Utils::Widen(e.what()));
        }
        catch (...)
        {
            SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE("An unknown exception occured while unloading RED4ext.");
        }

        break;
    }
    }

    return TRUE;
}
