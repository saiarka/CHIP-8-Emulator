

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(Test test.cpp memory_structure_tests.cpp)

target_link_libraries(Test Chip_Lib GTest::gtest GTest::gtest_main)






