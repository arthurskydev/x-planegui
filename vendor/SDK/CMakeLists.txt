set(CMAKE_CXX_STANDARD 20)

project(XPLM_SDK LANGUAGES CXX)



find_library(XPLM_LIBRARY NAMES XPLM PATHS "Libraries")
if (NOT XPLM_LIBRARY)
    message(FATAL_ERROR "X-Plane SDK not found")
endif()

message("XPLM was found: ${XPLM_LIBRARY}")
