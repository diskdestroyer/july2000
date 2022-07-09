cmake_minimum_required(VERSION 3.22.0)

project(july2000 LANGUAGES C CXX)

option(HOOKS "Build an injectable DLL." ON)
option(CNCNET "Include CnCNet patches." ON)

# set the output directory to ./build/
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/")

# set the output directory to ./build/ (multi-config)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/build/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/build/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/build/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/")

# build Debug by default
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
        message(NOTICE "++ No build type selected, defaulting to \"Debug\"")
        set(CMAKE_CONFIGURATION_TYPES "Debug")
        set(CMAKE_BUILD_TYPE "Debug")
endif()

# setup MSVC
if(MSVC)
        # turn off incremental linking when building Release
        if(CMAKE_CONFIGURATION_TYPES STREQUAL "Release"
        OR CMAKE_CONFIGURATION_TYPES STREQUAL "RelWithDebInfo")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /INCREMENTAL:NO")
        else()
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /INCREMENTAL")
        endif()

        # set warning level
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

        # suppress unsecure CRT warnings
        add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
        add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)

        # ignore warnings
        if(HOOKS)
                # unreferenced formal parameter
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4100")
        endif()

        if(CNCNET)
                # unreachable code
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4702")
        endif()
endif()

# setup MinGW
if(UNIX)
        # hint CMake that we are cross-compiling
        set(CMAKE_SYSTEM_NAME "Windows")

        # set compilers
        set(CMAKE_C_COMPILER "i686-w64-mingw32-gcc")
        set(CMAKE_CXX_COMPILER "i686-w64-mingw32-g++")

        # force 32-bit
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")

        # link CRT statically to avoid runtime MinGW dependencies
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")

        # set warning level
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

        # ignore warnings
        if(HOOKS)
                # ignore dll-specific warnings
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-attributes")

                # fix output filename for dll
                set(CMAKE_SHARED_LIBRARY_PREFIX "")
                set(CMAKE_SHARED_LIBRARY_SUFFIX ".dll")
        endif()
endif()

add_subdirectory("${CMAKE_SOURCE_DIR}/src/")

# copy the improvised injector into the output directory
file(COPY_FILE "${CMAKE_SOURCE_DIR}/src/hooks/bin/MSS32.DLL" "${CMAKE_BINARY_DIR}/MSS32.DLL")
