cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 20)

project(X-PlaneGui)

add_definitions(-DXPLM200=1 -DXPLM210=1 -DXPLM300=1 -DXPLM301=1 -DXPLM400=1)

if (APPLE)
    add_definitions(-DAPL)


else()
    message(FATAL_ERROR "Only Apple builds are supported at the moment")
endif()


if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_CXX_FLAGS_RELEASE "/MT")
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif()

add_subdirectory(vendor/imgui)

add_library(${PROJECT_NAME} STATIC src/Window.cpp include/X-PlaneGui/Window.h src/osx_clipboard.mm)

target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} ${XPLM_LIBRARY})
target_include_directories(${PROJECT_NAME} PUBLIC vendor/SDK/CHeaders/XPLM)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE include/X-PlaneGui)

if(APPLE)
    target_sources(${PROJECT_NAME} PRIVATE src/osx_clipboard.mm)
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL" "-framework AppKit")
endif()
if(WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32)
endif()
