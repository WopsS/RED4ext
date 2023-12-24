#pragma once
#include "ScriptCompiler.hpp"

namespace Hooks::ExecuteProcess
{
bool Attach();
bool Detach();
} // namespace Hooks::ExecuteProcess

bool ExecuteScc(SccApi& scc);
