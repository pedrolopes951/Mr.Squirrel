include_directories(../) #utils dir
add_executable(runtime_test runtime_test.cpp)
target_link_libraries(runtime_test PRIVATE utils)

add_test(NAME runtime_test COMMAND runtime_test)