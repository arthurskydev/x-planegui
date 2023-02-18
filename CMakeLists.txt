cmake_minimum_required(VERSION 3.9)
project(ImgX)

set(CMAKE_CXX_STANDARD 11)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_CXX_FLAGS_RELEASE "/MT")
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif()

include_directories(imgui src)

add_library(${PROJECT_NAME} STATIC src/imgwindow.cpp src/imgwindow.h src/osx_clipboard.mm)

if(APPLE)
    target_sources(${PROJECT_NAME} PRIVATE src/osx_clipboard.mm)
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL" "-framework AppKit")
endif()
if(WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32)
endif()
