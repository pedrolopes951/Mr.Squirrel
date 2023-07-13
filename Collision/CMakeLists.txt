# Add source files
set(SOURCES 
    Collision.cpp)


include_directories(${CMAKE_SOURCE_DIR}/PreCompiledHeader)
include_directories(${CMAKE_SOURCE_DIR}/utils)

# Create library
add_library(Collision ${SOURCES})


# Link SFML libraries
target_link_libraries(Collision PUBLIC MyPCH ${SFML_LIBS} ${OpenCV_LIBS} utils)
