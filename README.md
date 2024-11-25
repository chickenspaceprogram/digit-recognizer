# digit-recognizer

### A neural network to recognize handwritten digits from the MNIST dataset

This project is currently still in active development, so this README may be incomplete or out-of-date.

## How to run

To compile this project, you wiill have to install CMake, which can be downloaded [here](https://cmake.org/download/) or installed with your preferred package manager.

### MacOS

To compile this project, you'll need to install the following:

- [CMake](https://cmake.org/download/)
    - Alternately, you can install CMake through [HomeBrew](https://brew.sh/)
- XCode Command Line Developer tools
    - Open the app `Terminal`, and enter the command `xcode-select --install`

Then, use the terminal to navigate to the `build` directory. You can type `cd <directory>` to navigate into a directory (for example, `cd Desktop` will move into your Desktop), and `ls` to list the items in the current directory. 

Then, enter the following commands in order:

`cmake .`<br>
`cmake --build .`

You can then run the executable generated with `./digit-recognizer` (or by double-clicking on it in Finder).

### Windows

To compile this project, you will need to install the following: 

- [Microsoft Visual Studio](https://visualstudio.microsoft.com/)
    - Ensure that you select "Desktop Development with C++" in the Visual Studio Installer.


### Linux

You will need to install OpenBLAS through your package manager. Instructions for doing this are [here](https://github.com/OpenMathLib/OpenBLAS/wiki/Precompiled-installation-packages).

This project has only been tested on Fedora. You may or may not have to alter the build system a bit to get it to compile on other distributions, since other distributions may put OpenBLAS in different places.

### Notes

#### Fallback BLAS

Included in this project is a fallback version of BLAS. This version is likely much slower than the actual BLAS, but if you encounter errors when installing BLAS or building the project, you should try using the fallback version.

To use the fallback version, remove the lines in `src/libs/blas-wrapper.h` and `build/CMakeLists.txt` marked with the following text:

`##### remove this line to use the fallback version of BLAS #####`

If you use the fallback version of BLAS, you do not need to install BLAS.