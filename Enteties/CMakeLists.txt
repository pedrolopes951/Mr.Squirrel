# Add source files
set(SOURCES 
    Enteties.cpp)

# Create library
add_library(Enteties ${SOURCES})


# Link SFML libraries
target_link_libraries(Enteties PUBLIC MyPCH ${SFML_LIBS} MyPCH)
