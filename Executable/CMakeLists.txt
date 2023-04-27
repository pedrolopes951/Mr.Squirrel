# Add source files
set(SOURCES 
    main.cpp )

include_directories(${CMAKE_SOURCE_DIR}/PreCompiledHeader)
include_directories(${CMAKE_SOURCE_DIR}/Engine)
include_directories(${CMAKE_SOURCE_DIR}/Enteties)



# Create executable
add_executable(Game ${SOURCES})

# Link libraries
target_link_libraries(Game PRIVATE Engine Enteties ${SFML_LIBS} MyPCH)


