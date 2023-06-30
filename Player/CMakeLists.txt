# Add source files
set(SOURCES 
    Player.cpp)


include_directories(${CMAKE_SOURCE_DIR}/PreCompiledHeader)
include_directories(${CMAKE_SOURCE_DIR}/utils)

# Create library
add_library(Player ${SOURCES})


# Link SFML libraries
target_link_libraries(Player PUBLIC MyPCH ${SFML_LIBS} utils)
