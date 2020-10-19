project(tests)

add_subdirectory(googletest)

add_executable(tests Buffer.cpp Response.cpp)
target_link_libraries(tests gtest gtest_main libassignment-3)