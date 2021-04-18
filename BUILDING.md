# Building

The library can only be built on Windows. Below are the recommended steps to build it:

1. Download and install [Visual Studio 2019 Community Edition](https://www.visualstudio.com/) or a higher version.
2. Clone this repository.
3. Clone the dependencies (`git submodule update --init --recursive`).
4. Go to the `premake` directory and run `generate_projects.bat`.
5. Open the solution (`RED4ext.sln`) located in `projects` directory.
6. Build the projects.

The artifacts can be found in **build** directory.
