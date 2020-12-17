# RED4ext

A script extender for REDengine 4 ([Cyberpunk 2077](https://www.cyberpunk.net)).

## What is this library?

RED4ext is a library that extends REDengine 4. It will allow modders to add new features, modify the game behavior, add new
scripting functions or call existing ones in your own plugins.

This library is similar to:

* [Script Hook V](http://dev-c.com/GTAV/scripthookv)
* [Skyrim Script Extender](https://skse.silverlock.org/)

**Note**: Until more research and engine understanding is done consider this a playground and **use at your own risk**.

## Build instructions

### Windows

1. Download and install [Visual Studio 2019 Community Edition](https://www.visualstudio.com/) or a higher version.
2. Clone this repository.
3. Clone the dependencies (`git submodule update --init --recursive`).
4. Go to the `premake` directory and run `generate_projects.bat`.
5. Open the solution (`RED4ext.sln`) located in `projects` directory.
6. Build the projects.
