
#include <gtest/gtest.h>
#include "emulator_tests.h"

TEST_F(EmulatorTest3, Test0x3Jump) {
    test_emulator->mMemory.jump_to_memory(0x0230);
    ASSERT_EQ(*(test_emulator->mMemory.mprogram_counter), 0x36);
    test_emulator->mMemory.set_register_value(6, 0x2B);
    test_emulator->decode_execute();
    EXPECT_EQ((*test_emulator->mMemory.mprogram_counter), 0xDA);
}

TEST_F(EmulatorTest3, Test0x4Jump) {
    test_emulator->mMemory.jump_to_memory(0x0242);
    ASSERT_EQ(*(test_emulator->mMemory.mprogram_counter), 0x45);
    test_emulator->mMemory.set_register_value(5, 0x0);
    test_emulator->decode_execute();
    EXPECT_EQ((*test_emulator->mMemory.mprogram_counter), 0xDA);
}

TEST_F(EmulatorTest3, Test0x5Jump) {
    test_emulator->mMemory.jump_to_memory(0x0254);
    ASSERT_EQ(*(test_emulator->mMemory.mprogram_counter), 0x55);
    test_emulator->mMemory.set_register_value(5, 0x0);
    test_emulator->mMemory.set_register_value(6, 0x0);
    test_emulator->decode_execute();
    EXPECT_EQ((*test_emulator->mMemory.mprogram_counter), 0xDA);
}


TEST_F(EmulatorTest3, Test0x9Jump) {
    test_emulator->mMemory.jump_to_memory(0x027A);
    ASSERT_EQ(*(test_emulator->mMemory.mprogram_counter), 0x95);
    test_emulator->mMemory.set_register_value(5, 0x0);
    test_emulator->mMemory.set_register_value(6, 0x1);
    test_emulator->decode_execute();
    EXPECT_EQ((*test_emulator->mMemory.mprogram_counter), 0xDA);
}

TEST_F(EmulatorTest3, Test0x2Call) {
    test_emulator->mMemory.jump_to_memory(0x2A4);
    ASSERT_EQ(*(test_emulator->mMemory.mprogram_counter), 0x22);
    test_emulator->decode_execute();
    EXPECT_EQ(*(test_emulator->mMemory.mprogram_counter), 0x60);
    EXPECT_EQ(test_emulator->mMemory.mstack_index, 1);
    test_emulator->mMemory.jump_to_memory(0x204);
    test_emulator->decode_execute();
    EXPECT_EQ(test_emulator->mMemory.mstack_index, 0);
    EXPECT_EQ(*(test_emulator->mMemory.mprogram_counter), 0xA4);
}

TEST_F(EmulatorTest, Test0x8XY0) {
    test_emulator->mMemory.set_register_value(0x0000, 1);
    test_emulator->mMemory.set_register_value(0x0001, 2);

    test_emulator->eight_instructions(0x8010);
    uint8_t V0 = test_emulator->mMemory.read_register_value(0x0000);
    uint8_t V1 = test_emulator->mMemory.read_register_value(0x0001);
    EXPECT_EQ(V0, V1);
}

TEST_F(EmulatorTest, Test0x8XY1) {
    test_emulator->mMemory.set_register_value(0x0000, 1);
    test_emulator->mMemory.set_register_value(0x0001, 2);

    test_emulator->eight_instructions(0x8011);
    uint8_t V0 = test_emulator->mMemory.read_register_value(0x0000);
    EXPECT_EQ(V0, 1 | 2);
}

TEST_F(EmulatorTest, Test0x8XY2) {
    test_emulator->mMemory.set_register_value(0x0000, 1);
    test_emulator->mMemory.set_register_value(0x0001, 2);

    test_emulator->eight_instructions(0x8012);
    uint8_t V0 = test_emulator->mMemory.read_register_value(0x0000);
    EXPECT_EQ(V0, 1 & 2);
}


TEST_F(EmulatorTest, Test0x8XY3) {
    test_emulator->mMemory.set_register_value(0x0000, 1);
    test_emulator->mMemory.set_register_value(0x0001, 2);

    test_emulator->eight_instructions(0x8013);
    uint8_t V0 = test_emulator->mMemory.read_register_value(0x0000);
    EXPECT_EQ(V0, 1 ^ 2);
}


TEST_F(EmulatorTest, Test0x8XY4) {
    test_emulator->mMemory.set_register_value(0x0000, 255);
    test_emulator->mMemory.set_register_value(0x0001, 255);
    
    test_emulator->eight_instructions(0x8014);
    uint8_t V0 = test_emulator->mMemory.read_register_value(0x0000);
    uint8_t VF = test_emulator->mMemory.read_register_value(0x000F);
    uint8_t sum = static_cast<uint8_t>(255) + static_cast<uint8_t>(255);
    EXPECT_EQ(VF, 1);
    EXPECT_EQ(V0, sum);
}


TEST_F(EmulatorTest, Test0x8XY5) {
    test_emulator->mMemory.set_register_value(0x0000, 0);
    test_emulator->mMemory.set_register_value(0x0001, 10);
    
    test_emulator->eight_instructions(0x8015);
    uint8_t V0 = test_emulator->mMemory.read_register_value(0x0000);
    uint8_t VF = test_emulator->mMemory.read_register_value(0x000F);
    uint8_t diff = static_cast<uint8_t>(0) - static_cast<uint8_t>(10);
    EXPECT_EQ(VF, 0);
    EXPECT_EQ(V0, diff);
}

TEST_F(EmulatorTest, Test0x8XY6) {
    test_emulator->mMemory.set_register_value(0x0000, 1);
    
    test_emulator->eight_instructions(0x8016);
    uint8_t V0 = test_emulator->mMemory.read_register_value(0x0000);
    uint8_t VF = test_emulator->mMemory.read_register_value(0x000F);
    EXPECT_EQ(VF, 1);
    EXPECT_EQ(V0, 0);
}

TEST_F(EmulatorTest, Test0x8XY7) {
    test_emulator->mMemory.set_register_value(0x0000, 10);
    test_emulator->mMemory.set_register_value(0x0001, 0);
    
    test_emulator->eight_instructions(0x8017);
    uint8_t V0 = test_emulator->mMemory.read_register_value(0x0000);
    uint8_t VF = test_emulator->mMemory.read_register_value(0x000F);
    uint8_t sum = static_cast<uint8_t>(0) - static_cast<uint8_t>(10);
    EXPECT_EQ(VF, 0);
    EXPECT_EQ(V0, sum);
}


TEST_F(EmulatorTest, Test0x8XYE) {
    test_emulator->mMemory.set_register_value(0x0000, 0x80);
    
    test_emulator->eight_instructions(0x801E);
    uint8_t V0 = test_emulator->mMemory.read_register_value(0x0000);
    uint8_t VF = test_emulator->mMemory.read_register_value(0x000F);
    EXPECT_EQ(VF, 1);
    EXPECT_EQ(V0, 0);
}


TEST_F(EmulatorTest, Test0xFX1E) {
    test_emulator->mMemory.set_register_value(0x0000, 1);
    test_emulator->mMemory.set_address_register(0x0200);
    test_emulator->fifteen_instructions(0xF01E);
    EXPECT_EQ(test_emulator->mMemory.read_address_register(), 0x0200 + 1);
}


TEST_F(EmulatorTest, TestRegDump) {
    test_emulator->mMemory.set_register_value(0x0000, 0xFF);
    test_emulator->mMemory.set_register_value(0x0001, 0xF1);
    test_emulator->mMemory.set_address_register(0x0200);
    test_emulator->reg_dump(0xF155, test_emulator->mMemory.read_address_register());
    EXPECT_EQ(test_emulator->mMemory.read_memory_at(0x0200), 0xFF);
    EXPECT_EQ(test_emulator->mMemory.read_memory_at(0x0201), 0xF1);
}

TEST_F(EmulatorTest, TestRegLoad) {
    test_emulator->mMemory.set_address_register(0x0200);
    test_emulator->reg_load(0xF165, test_emulator->mMemory.read_address_register());
    EXPECT_EQ(test_emulator->mMemory.read_register_value(0x0000), 0x00);
    EXPECT_EQ(test_emulator->mMemory.read_register_value(0x0001), 0xE0);
}


























