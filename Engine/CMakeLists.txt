# Add source files
set(SOURCES 
    Engine.cpp)

include_directories(${CMAKE_SOURCE_DIR}/PreCompiledHeader)

    # Create library
add_library(Engine ${SOURCES})



# Link SFML libraries
target_link_libraries(Engine PUBLIC MyPCH ${SFML_LIBS})
