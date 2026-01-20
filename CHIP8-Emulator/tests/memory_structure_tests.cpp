
#include <gtest/gtest.h>
#include "memory_structure_tests.h"
#include <iostream>
#include <iomanip>
//TODO: Fix include (is directory specific)


TEST_F(Memory_StructureTest, TestGetInstruction) {
    uint16_t inst = test_memory->get_current_instruction();
    EXPECT_TRUE(inst == 0x00E0) << "value of inst is : " << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(inst);
}

TEST_F(Memory_StructureTest, TestIncrementInstruction) {
    uint16_t prev_inst = test_memory->get_current_instruction();
    uint16_t increment_inst = test_memory->get_current_instruction();
    EXPECT_TRUE(increment_inst == 0x6101) << "value of inst is : " << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(increment_inst);
}




