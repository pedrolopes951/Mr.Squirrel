
add_definitions(-DTexturesPATH="${CMAKE_BINARY_DIR}/Textures/")
add_definitions(-DFONTPATH="${CMAKE_BINARY_DIR}/Fonts/")

# Add source files
set(SOURCES 
    Engine.cpp)

include_directories(${CMAKE_SOURCE_DIR}/PreCompiledHeader)
include_directories(${CMAKE_SOURCE_DIR}/Enteties)



    # Create library
add_library(Engine ${SOURCES})



# Link SFML libraries
target_link_libraries(Engine PUBLIC MyPCH ${SFML_LIBS})
