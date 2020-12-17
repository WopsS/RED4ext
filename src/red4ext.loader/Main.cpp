#include <stdafx.hpp>
#include <App.hpp>

int wmain(int aArgc, wchar_t* aArgv[], wchar_t* aEnvp[])
{
    RED4ext::App app;

    auto result = app.Init();
    if (result)
    {
        return result.value();
    }

    // Get all arguments, except the exe path.
    std::wstringstream cmdLineBuilder;
    for (int32_t i = 1; i < aArgc; i++)
    {
        cmdLineBuilder << aArgv[i];
        if (i < aArgc - 1)
        {
            cmdLineBuilder << L" ";
        }
    }

    auto cmdLine = cmdLineBuilder.str();

    result = app.Run(cmdLine.data());
    if (result)
    {
        return result.value();
    }

    result = app.Shutdown();
    return result.value();
}
