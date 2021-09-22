#pragma once

#include "Config.hpp"

class DevConsole
{
public:
    DevConsole(const Config& aConfig);
    ~DevConsole();

    bool IsOutputRedirected() const;

private:

    bool m_isCreated;
    bool m_isRedirected;
};
