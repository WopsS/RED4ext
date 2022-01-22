#pragma once

#include "Config.hpp"

class DevConsole
{
public:
    DevConsole(const Config::DevConfig& aConfig);
    ~DevConsole();

    bool IsOutputRedirected() const;

private:
    bool m_isCreated;

    FILE* m_stdoutStream;
    FILE* m_stderrStream;
};
