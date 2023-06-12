cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (CMAKE_CXX_FLAGS "-O0 -g -Wall")
project(SideScroller)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML library
find_package(SFML 2.5 REQUIRED system window graphics network audio)
set(SFML_LIBS sfml-system sfml-window sfml-graphics sfml-network sfml-audio)


find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
message(STATUS "OpenCV include directories: ${OpenCV_INCLUDE_DIRS}")

add_definitions(-DTexturesPATH="${CMAKE_BINARY_DIR}/Textures/")
add_definitions(-DFONTPATH="${CMAKE_BINARY_DIR}/Fonts/")

add_subdirectory(Engine)
add_subdirectory(Enteties)
add_subdirectory(Executable)
add_subdirectory(Player)

 

# Create the Fonts directory in the binary directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Fonts)   


file(COPY ${CMAKE_SOURCE_DIR}/Fonts/
    DESTINATION ${CMAKE_BINARY_DIR}/Fonts/)


# Tell CMake that the Fonts directory should be included in the install step
install(DIRECTORY ${CMAKE_BINARY_DIR}/Fonts/
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)

# Create the Textures directory in the binary directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Textures/)  

 
file(COPY ${CMAKE_SOURCE_DIR}/Textures/ 
    DESTINATION ${CMAKE_BINARY_DIR}/Textures/)


# Tell CMake that the Textures directory should be included in the install step 
install(DIRECTORY ${CMAKE_BINARY_DIR}/Textures 
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)  


# Create the precompiled header
set(PCH_HEADER "PreCompiledHeader/stdafx.hpp")
set(PCH_SOURCE "PreCompiledHeader/stdafx.cpp")
set(PCH_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(MyPCH STATIC ${PCH_SOURCE})
target_include_directories(MyPCH PUBLIC ${PCH_INCLUDE_DIRS})
target_compile_features(MyPCH PUBLIC cxx_std_11)
target_compile_options(MyPCH PRIVATE -Winvalid-pch)
target_precompile_headers(MyPCH PUBLIC ${PCH_HEADER})



