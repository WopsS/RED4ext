# How to install

RED4ext can be installed in two ways:

1. [Using RED4ext's loader](#Using-RED4exts-loader).
2. [Using another loader](#Using-another-loader).

## Using RED4ext's loader

The installation of the extender using RED4ext's loader can be done in two ways:

### First way (Precompiled artifacts)

1. Download the compiled artifacts from the [Releases](https://github.com/WopsS/RED4ext/releases) page.
2. Extract the content of the archive in the game's directory.

### Second way (Building from source)

1. Create a new directory named `red4ext` in the game's directory.
2. Copy `RED4ext.dll` in `red4ext` directory created previously.
3. Copy `version.dll` in `game_directory/bin/x64`.

## Using another loader

If you want to use another loader (for example [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader)),
just copy `RED4ext.dll` (and rename, if necessary) to the directory that the loader is using for loading plugins.
