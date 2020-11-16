# Most of this cmake file is from the SFML Dev book

cmake_minimum_required(VERSION 3.17)
project(SFMLTurboHiker)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

set(CMAKE_CXX_STANDARD 11)

set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Use static SFML librares")

if (SFML_STATIC_LIBRARIES)
    add_definitions(-DSFML_STATIC)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif()
endif()


# Path to FindSFML.cmake
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/;${CMAKE_MODULE_PATH}")

add_executable(SFMLTurboHiker
                main.cpp
                src/Animation.cpp)

find_package(SFML 2 COMPONENTS audio graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(SFMLTurboHiker ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

#if(SFML_FOUND)
#    include_directories(${SFML_INCLUDE_DIR})
#else()
#    set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
#    message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
#    message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
#endif()


