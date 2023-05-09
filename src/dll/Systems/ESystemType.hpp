#pragma once

enum class ESystemType : uint8_t
{
    /*
     * Ordering the system based on the initialization order.
     */

    Logger,
    Hooking,
    Script,
    State,
    Plugin
};
