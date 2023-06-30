# Add source files
set(SOURCES 
    Enteties.cpp)


include_directories(${CMAKE_SOURCE_DIR}/PreCompiledHeader)
include_directories(${CMAKE_SOURCE_DIR}/utils)

# Create library
add_library(Enteties ${SOURCES})


# Link SFML libraries
target_link_libraries(Enteties PUBLIC MyPCH ${SFML_LIBS} ${OpenCV_LIBS} utils)
