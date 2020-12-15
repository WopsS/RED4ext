#include <stdafx.hpp>
#include <REDext/REDext.hpp>

#include <App.hpp>
REDEXT_EXPORT void OnBaseInitialization()
{
    auto app = App::Get();
    app->Init();
}

REDEXT_EXPORT void OnInitialization()
{
}

REDEXT_EXPORT void OnUpdate()
{
    auto app = App::Get();
    app->Run();
}

REDEXT_EXPORT void OnShutdown()
{
    auto app = App::Get();
    app->Shutdown();
}
