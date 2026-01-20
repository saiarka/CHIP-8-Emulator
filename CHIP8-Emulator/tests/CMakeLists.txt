

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 9156d4caac880b513264ecbe0aa4746a3fead3d7
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(Test test.cpp memory_structure_tests.cpp)

target_link_libraries(Test Chip_Lib GTest::gtest_main)






