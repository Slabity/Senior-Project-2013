Senior-Project-2013
=========

Platformer Game created using SDL, OpenGL, and C++

This project is no longer maintained. It uses a deprecated version of both SDL (1.2) and OpenGL (1.x), along with some lesser quality C++ formatting. Please feel free to fork or use any available code for personal projects.

Installation
=========

There is no support for compilation on Windows.

Navigate to the project's root folder and use the CMake utility to generate either a Makefile (Linux) or an Xcode Project (Mac OS X)

    cmake .
    make            #If using the Make utility

After compilation, the program will be compiled and placed in the bin/ directory. You can either double click it in a file browser, or run it in the terminal.

    ./bin/SProject2013

Cleanup
=========

To clean all temporary files (including the project application), simply run the shell script in the root directory. It will automatically take care of the folders

    sh clean.sh
