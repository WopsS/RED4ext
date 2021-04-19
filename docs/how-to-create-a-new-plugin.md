# How to create a new plugin

To create a new plugin you can whatever build systen / toolchain you would like, as long as the output is
compatible with x86-64 architecture and with `__fastcall` calling convention.

Some examples you can use one of the following:

* [CMake](https://cmake.org/)
* [Premake](https://premake.github.io/)
* [Visual Studio](https://visualstudio.microsoft.com/)

After you decide what build systen or toolchain you would like to use make sure to add [RED4ext.SDK](https://github.com/WopsS/RED4ext.SDK)
to project's include paths. This dependency is necessary since it provides the API that RED4ext is using to load the plugin, as well as the
game's structures that you might need.

Your mod should export few functions in order to be loaded correctly (see below which functions needs to be exported),
to export a function from C/C++ you can use RED4ext's helpers, `RED4EXT_C_EXPORT` (equivalent of `extern "C" __declspec(dllexport)`)
and `RED4EXT_CALL` (equivalent of `__fastcall`).

## Necessary exported functions

### Supports

Returns the support API version supported by your plugins.

---

### Query

This function is used to fill your plugin information, like name, author, supported game version, etc..

#### Parameters

* **RED4ext::PluginInfo\*** - The pointer to the structure that contains information about your plugin.

#### Notes

**Do not** do anything in this function yet (like creating a hook or allocating a trampoline).

Runtime version is the game's version that your plugins support, if your plugin has runtime set to `1.21` your plugin will be loaded **only** if the game's
version is `1.21`, else it would not be loaded. It is recommended to set it to `RED4EXT_RUNTIME_LATEST` to target
the latest game's version that the SDK defined.

If you want to use RED4ext only as a loader and you do not care about game's version use `RED4EXT_RUNTIME_INDEPENDENT`.

---

### Load

An optional function called when the plugin is loaded. Anything can be done here at this point, register functions, call scripting functions, etc..

#### Parameters

* **RED4ext::PluginHandle** - The unique indentifier of your plugin.
* **const RED4ext::IRED4ext\*** - The pointer to RED4ext interface.

#### Return value

Return `true` if your initalization succeeded, otherwise `false`. Returning `false` will also call `Unload`.

#### Notes

All hooks created here will be attached automatically later, you do not need to attach them manually.
Be sure to store the plugin handle and the interface because you cannot get it again later. The plugin handle is what identify your plugin through the extender.

---

### Unload

The unload function, called when the plugin is unloaded.

## Other functions

### PostLoad

Called after all plugins are loaded, here a plugin interface can be requested or any additional initializations.

#### Notes

All hooks created here will **not** be attached automatically, you **must** attach them manually.
