# Building

The library can only be built on Windows. Below are the recommended steps to build it:

1. Download and install [Visual Studio 2022 Community Edition](https://www.visualstudio.com/) or a newer version.
2. Clone this repository.
3. Clone the dependencies (`git submodule update --init --recursive`).
4. Download and extract the content of [Premake 5](https://github.com/premake/premake-core/releases) in `premake` directory.
5. Go to the `premake` directory and run `generate_projects.bat`.
6. Open the solution (`RED4ext.sln`) located in `projects` directory.
7. Build the projects.

The artifacts can be found in **build** directory.
