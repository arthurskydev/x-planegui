cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 20)

project(X-PlaneGui)

add_subdirectory(vendor/imgui)

if (APPLE)
    find_library(XPLM_LIBRARY NAMES XPLM PATHS vendor/SDK/Libraries/Mac)
endif()
if (NOT XPLM_LIBRARY)
    message(FATAL_ERROR "X-Plane SDK not found")
endif()

message("XPLM was found: ${XPLM_LIBRARY}")


if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_CXX_FLAGS_RELEASE "/MT")
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif()

add_library(${PROJECT_NAME} STATIC src/Window.cpp include/X-PlaneGui/Window.h src/osx_clipboard.mm include/X-PlaneGui/FontHelpers.h)

target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC ${XPLM_LIBRARY})
target_include_directories(${PROJECT_NAME} PUBLIC vendor/SDK/CHeaders/XPLM)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE include/X-PlaneGui)

if(APPLE)
    target_sources(${PROJECT_NAME} PRIVATE src/osx_clipboard.mm)
    target_link_libraries(${PROJECT_NAME} PUBLIC "-framework OpenGL" "-framework AppKit")
endif()
if(WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32)
endif()
