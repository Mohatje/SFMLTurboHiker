cmake_minimum_required(VERSION 3.15)
project(SFMLTurboHiker)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

set(CMAKE_CXX_STANDARD 11)

set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Use static SFML librares")

############################ HOW TO RUN ON WINDOWS ############################
# - Make sure that the env variable SFML_ROOT is properly set
# - Make sure that {SFML_ROOT}/bin is added to the system path


if (SFML_STATIC_LIBRARIES)
    add_definitions(-DSFML_STATIC)
endif()

ADD_LIBRARY(TurboHikerLogic STATIC
            src/Logic/AbstractFactory.cpp
            src/Logic/Entity.cpp
            src/Logic/EntityFactory.cpp
            src/Logic/FactoryCreator.cpp
            src/Logic/HelperFunctions.cpp
            src/Logic/Random.cpp
            src/Logic/Player.cpp
            src/Logic/World.cpp
            src/Logic/PassingHiker1.cpp
            src/Logic/PassingHiker2.cpp
            src/Logic/GameAI.cpp)

ADD_LIBRARY(INIConfiguration STATIC
            src/Parser/ini_configuration.cc src/assertion.h)


# Path to FindSFML.cmake
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/" ${CMAKE_MODULE_PATH})

add_executable(SFMLTurboHiker
                main.cpp
                src/Display/Animation.cpp
                src/Display/Transformation.cpp
                src/Display/AssetManager.cpp
                src/Display/Player.cpp
                src/Display/KeyConfigHelper.cpp
                src/Display/FactoryCreator.cpp
                src/Display/EntityFactory.cpp
                src/Display/Game.cpp
                src/Display/State.cpp
                src/Display/World.cpp
                src/Display/TileEntity.cpp
                src/Display/PassingHiker1.cpp
                src/Display/PassingHiker2.cpp)


find_package(SFML 2 COMPONENTS audio graphics window system REQUIRED)


include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(SFMLTurboHiker ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_link_libraries(SFMLTurboHiker TurboHikerLogic)
target_link_libraries(SFMLTurboHiker INIConfiguration)

add_custom_command(TARGET SFMLTurboHiker POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/Config/ $<TARGET_FILE_DIR:SFMLTurboHiker>/Config)

add_custom_command(TARGET SFMLTurboHiker POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/media/ $<TARGET_FILE_DIR:SFMLTurboHiker>/media)


