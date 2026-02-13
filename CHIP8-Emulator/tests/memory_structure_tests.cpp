
#include <gtest/gtest.h>
#include "memory_structure_tests.h"
#include <iostream>
#include <iomanip>


TEST_F(Memory_StructureTest, TestGetInstruction) {
    uint16_t inst = test_memory->get_current_instruction();
    EXPECT_TRUE(inst == 0x00E0) << "value of inst is : " << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(inst);
}

TEST_F(Memory_StructureTest, TestIncrementInstruction) {
    uint16_t prev_inst = test_memory->get_current_instruction();
    uint16_t increment_inst = test_memory->get_current_instruction();
    EXPECT_TRUE(increment_inst == 0x6101) << "value of inst is : " << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(increment_inst);
}
/*
TEST_F(Memory_StructureTest, TestIncrementStack) {
   test_memory->increment_stack();
   uint16_t inst = test_memory->get_current_instruction();
   EXPECT_TRUE(inst == 0x00E0) << "value of inst after increment is : " << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(inst);
   EXPECT_TRUE(test_memory->mstack_chunk[test_memory->mstack_index] == 0);
   EXPECT_TRUE(test_memory->mstack_chunk[test_memory->mstack_index - 1] == (uint64_t) test_memory->mprogram_counter) << "stack memory not correctly filled";
}

TEST_F(Memory_StructureTest, TestDecrementStack) {
   test_memory->increment_stack();
   test_memory->decrement_stack();
   uint16_t inst = test_memory->get_current_instruction();
   EXPECT_TRUE(inst == 0x6101) << "value of inst at program counter after decrement is :" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(inst);
   EXPECT_TRUE(test_memory->mstack_chunk[test_memory->mstack_index] == 0);
}
*/
TEST_F(Memory_StructureTest, TestSetRegisterValue) {
   uint8_t V5_value = test_memory->read_register_value(0x0005);
   EXPECT_TRUE(V5_value == 0);
   test_memory->set_register_value(0x0005, 0x02);
   V5_value = test_memory->read_register_value(0x0005);
   EXPECT_TRUE(V5_value == 0x02);
}

TEST_F(Memory_StructureTest, TestReadMemory) {
    uint8_t memory_read = test_memory->read_memory_at(0x0200);
    EXPECT_TRUE(memory_read == 0x00);
    memory_read = test_memory->read_memory_at(0x0201);
    EXPECT_TRUE(memory_read == 0xE0);
}

TEST_F(Memory_StructureTest, TestSetMemory) {
    test_memory->set_memory_at(0x0200, 0x1001);
    EXPECT_TRUE(test_memory->read_memory_at(0x0200) == 0x10);
    EXPECT_TRUE(test_memory->read_memory_at(0x0201) == 0x01);
}

TEST_F(Memory_StructureTest, TestMemoryJump) {
    EXPECT_TRUE(test_memory->get_current_instruction() == 0x00E0);
    test_memory->jump_to_memory(0x0202);
    EXPECT_TRUE(test_memory->get_current_instruction() == 0x6101);
}


