# Add source files
set(SOURCES 
    main.cpp )

include_directories(${CMAKE_SOURCE_DIR}/PreCompiledHeader)
include_directories(${CMAKE_SOURCE_DIR}/Engine)
include_directories(${CMAKE_SOURCE_DIR}/Enteties)
include_directories(${CMAKE_SOURCE_DIR}/Player)
include_directories(${CMAKE_SOURCE_DIR}/utils)




# Create executable
add_executable(Game ${SOURCES})

# Link libraries
target_link_libraries(Game PUBLIC Engine Enteties Player ${SFML_LIBS} MyPCH utils)


