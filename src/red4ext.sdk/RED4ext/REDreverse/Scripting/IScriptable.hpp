#pragma once

#include <RED4ext/REDreverse/ISerializable.hpp>

namespace RED4ext::REDreverse::Scripting
{
    struct IScriptable : ISerializable
    {
    };

    RED4EXT_ASSERT_SIZE(IScriptable, 0x8);
}
