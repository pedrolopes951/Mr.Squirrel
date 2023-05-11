

# Add source files
set(SOURCES 
    Engine.cpp)

include_directories(${CMAKE_SOURCE_DIR}/PreCompiledHeader)
include_directories(${CMAKE_SOURCE_DIR}/Enteties)
include_directories(${CMAKE_SOURCE_DIR}/Player)




    # Create library
add_library(Engine ${SOURCES})



# Link SFML libraries
target_link_libraries(Engine PUBLIC MyPCH ${SFML_LIBS})
