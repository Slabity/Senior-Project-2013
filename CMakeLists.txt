cmake_minimum_required(VERSION 2.8)
project(SProject2013 CXX)
enable_language(C)

#Create the bin directory.
file(MAKE_DIRECTORY bin)

#Copy the data folder as well
file(COPY assets/data DESTINATION bin)

#Set the executable to create the binary in bin/
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /Library/Frameworks/)

#Make sure that proper SDL libraries are found and linked.
Find_Package(SDL REQUIRED)
Find_Package(OpenGL REQUIRED)
Find_Package(SDL_image REQUIRED)

#Set the compiler to use the following files.
set(SOURCES src/main.cpp
            src/Application.cpp
            src/Scene.cpp
            src/Image.cpp
            src/PrototypeScene.cpp
            src/SceneObject.cpp
            src/Camera.cpp
            src/Vector2d.cpp
            src/CollisionController.cpp
            src/Polygon.cpp
            src/Player.cpp)


if(APPLE)
    set(SOURCES ${SOURCES} src/Mac/SDLMain.m)
endif(APPLE)

#Link SDL to the application.
set(LINKED_LIBRARIES ${SDL_LIBRARY}
                     ${OPENGL_LIBRARY}
                     ${SDLIMAGE_LIBRARY}
                     ${SDLTTF_LIBRARY})

#Set flags.
set(CMAKE_CXX_FLAGS "-ggdb -I/usr/include/SDL")

#Create the executable.
add_executable(SProject2013 ${SOURCES})

Target_Link_Libraries(SProject2013 ${LINKED_LIBRARIES})
