#pragma once

#include "ESystemType.hpp"

class ISystem
{
public:
    virtual ~ISystem() = default;

    virtual ESystemType GetType() = 0;

    virtual void Startup() = 0;
    virtual void Shutdown() = 0;
};
