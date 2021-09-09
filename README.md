# Almond Editor ![License](https://img.shields.io/github/license/enix403/Almond#1)

(An ongoing attempt to create) A simple 3D model editor.

Almond is an early stage simple and interactive 3D model editor. Not much is implemented currently.  
*Note: This is just a hobby project, nothing serious.*

## Getting Started

Almond is written in **C++17** and uses CMake as its build system. It is being developed primarily on Linux and is untested on other platforms such as Windows. It uses **OpenGL** as rendering backend.

1. Start by cloning this repository and then run `git submodule update --init` to fetch the dependencies.

2. **Get the required stuff:**

    Almond requires **OpenGL 4.2** or newer to be installed on your system. Make sure you have the following dependencies installed on your system.
    - A C/C++ Compiler (Almond is tested with *gcc* and *clang*)
    - CMake (**3.10** or newer)
    - pkg-config
    - GLFW3 *(libglfw)*
      - Ensure that GLFW3 is accessible by pkg-config  by runnning `pkg-config --cflags --libs glfw3` and verifying that the output of the command is non-empty. (If it is empty then something is wrong)

    Follow the instructions below for your operating system to install the above dependencies.

    - **Arch Linux / Manjaro**
    
       ```shell-script
       pacman -S cmake base-devel pkgconf glfw-x11 # replace glfw-x11 with glfw-wayland if you're using wayland
       ```

    - **Ubuntu / Debian**

       ```shell-script
       apt update
       apt install cmake build-essential pkg-config libglfw3-dev
       ```

    - **Other Distros / Operating Systems**

      Use your system's preferred method (i.e a package manager) to install the above mentioned dependencies.


3. **Generate build files:**

    Run the `GenBuildFiles.sh` utility script to generate build files.
    ```shell-script
    ./GenBuildFiles.sh Debug # or Release
    ```
    ------
    _You can pass additional arguments, which will be passed over to the `cmake` command. You can also choose which compiler to use using the `CC` and `CXX` environment variables. **Example:**_
    ```shell-script
    CC=/usr/bin/clang CXX=/usr/bin/clang++ ./GenBuildFiles.sh Release -G Ninja
    ```
    _This will generate a Release build config using clang as compiler, and use [Ninja build system][ninja-link] instead of the default one._


4. **Compile the project:**

    Open up a terminal, `cd` into `PROJECT_ROOT/build/debug` (or `PROJECT_ROOT/build/release`) and invoke your build system (e.g make).
    ```shell-script
    make -j8
    ```

5. **Run the editor:**

    Navigate to the project root and run:
    ```shell-script
    build/debug/bin/almond # or build/release/bin/almond
    ```


[ninja-link]: https://ninja-build.org
[cmake-link]: https://cmake.org/download/
