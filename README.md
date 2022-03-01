# RED4ext

A script extender for REDengine 4 ([Cyberpunk 2077](https://www.cyberpunk.net)).

## About this library

RED4ext is a library that extends REDengine 4. It will allow modders to add new features, modify the game behavior, add new
scripting functions or call existing ones in your own plugins.

This library is similar to:

* [Script Hook V](http://dev-c.com/GTAV/scripthookv)
* [Skyrim Script Extender](https://skse.silverlock.org/)

This library is split into two parts:

* [RED4ext](https://github.com/WopsS/RED4ext) - This project which consist of the loader, it only takes care of managing plugins.
* [RED4ext.SDK](https://github.com/WopsS/RED4ext.SDK) - This project contains the reversed types and helpers to extend the engine, it can be used independently of RED4ext.

If you are developing a new plugin, add only [RED4ext.SDK](https://github.com/WopsS/RED4ext.SDK) in your project structure.

## How to install

Instructions about how to install RED4ext can be found [here](https://docs.red4ext.com/).

## Building from source

Instructions about how to build RED4ext can be found in [BUILDING.md](/BUILDING.md).

## Contributing

Do you want to contribute? Community feedback and contributions are highly appreciated!

**For general rules and guidelines see [CONTRIBUTING.md](/CONTRIBUTING.md).**
