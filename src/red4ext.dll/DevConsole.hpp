#pragma once

#include "Config.hpp"

class DevConsole
{
public:
    DevConsole(const Config& aConfig);
    ~DevConsole();

    bool IsOpen() const;

private:

    bool m_isCreated;
    bool m_isOpen;
};
