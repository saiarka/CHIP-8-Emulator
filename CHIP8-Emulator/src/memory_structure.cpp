
#include "memory_structure.h"
#include "emulator_exceptions.h"
#include <fstream>
#include <iostream>
#include <iomanip>

Memory_Structure::Memory_Structure(std::ifstream& rom_stream, int rom_size) {
    mmemory_chunk = std::vector<uint8_t>(4096, 0);
    rom_stream.read(reinterpret_cast<char*>(mmemory_chunk.data() + 512), static_cast<std::streamsize>(rom_size));
    mprogram_counter = mmemory_chunk.data() + 512;

    mstack_chunk = std::vector<uint64_t>(16, 0);
    mstack_pointer = mstack_chunk.data();

V0 = 0;
    V1 = 0;
    V2 = 0;
    V3 = 0;
    V4 = 0;
    V5 = 0;
    V6 = 0;
    V7 = 0;
    V8 = 0;
    V9 = 0;
    VA = 0;
    VB = 0;
    VC = 0;
    VD = 0;
    VE = 0;
    VF = 0;

    address_register = 0;
};

Memory_Structure::~Memory_Structure() {

    mprogram_counter = nullptr;
    mstack_pointer = nullptr;

};

void Memory_Structure::print_memory() {
    for(int i = 0; i < mmemory_chunk.size(); i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(mmemory_chunk[i]);
        if (i % 10 == 0) {std::cout << std::endl;}
    }
};

void Memory_Structure::increment_program_counter() {
    mprogram_counter += 2;
};

uint16_t Memory_Structure::get_current_instruction() {

    uint8_t hex_1 = *mprogram_counter;
    uint8_t hex_2 = *(mprogram_counter + 1);
    uint16_t inst = ((uint16_t)hex_1 << 8) | (uint16_t)hex_2;
    increment_program_counter();

    return inst;

};

//TODO: Test
void Memory_Structure::jump_to_memory(uint16_t memory_address) {
    if (memory_address >= 4096 || memory_address < 0) { throw CHIP_8_Emulator::CPU_Exception("Out Of Range Memory Access"); }
    mprogram_counter = mmemory_chunk.data() + memory_address;
};

//TODO: Test 
void Memory_Structure::set_memory_at(uint16_t memory_address, uint16_t new_memory) {
    if (memory_address >= 4096 || memory_address < 0) { throw CHIP_8_Emulator::CPU_Exception("Out Of Range Memory Access"); }
    uint8_t first_half = (new_memory >> 8);
    uint8_t second_half = (new_memory & 0x00FF);
    mmemory_chunk[memory_address] = first_half;
    mmemory_chunk[memory_address+1] = second_half;
};

//TODO: Test
uint8_t Memory_Structure::read_memory_at(uint16_t memory_address) const {
    return mmemory_chunk[memory_address];
}

//TODO: Test, Check for more robust edge case handling
uint8_t Memory_Structure::read_register_value(uint16_t X) const{

    switch(X) {
        case 0x0000:
            return V0;
        case 0x0001:
            return V1;
        case 0x0002:
            return V2;
        case 0x0003:
            return V3;
        case 0x0004:
            return V4;
        case 0x0005:
            return V5;
        case 0x0006:
            return V6;
        case 0x0007:
            return V7;
        case 0x0008:
            return V8;
        case 0x0009:
            return V9;
        case 0x000A:
            return VA;
        case 0x000B:
            return VB;
        case 0x000C:
            return VC;
        case 0x000D:
            return VD;
        case 0x000E:
            return VE;
        case 0x000F:
            return VF;
        default:
            std::cout << "ATTENTION: DEFAULT REGISTER VALUE AT VF RETURNED" << std::endl;
            throw CHIP_8_Emulator::CPU_Exception("Invalid Register Error");
    }

};

//TODO: Test
//Add protection against setting VF to anything other than 0 or 1
void Memory_Structure::set_register_value(uint16_t X, uint8_t new_value){
    switch(X) {
        case 0x0000:
            V0 = new_value;
            break;
        case 0x0001:
            V1 = new_value;
            break;
        case 0x0002:
            V2 = new_value;
            break;
        case 0x0003:
            V3 = new_value;
            break;
        case 0x0004:
            V4 = new_value;
            break;
        case 0x0005:
            V5 = new_value;
            break;
        case 0x0006:
            V6 = new_value;
            break;
        case 0x0007:
            V7 = new_value;
            break;
        case 0x0008:
            V8 = new_value;
            break;
        case 0x0009:
            V9 = new_value;
            break;
        case 0x000A:
            VA = new_value;
            break;
        case 0x000B:
            VB = new_value;
            break;
        case 0x000C:
            VC = new_value;
            break;
        case 0x000D:
            VD = new_value;
            break;
        case 0x000E:
            VE = new_value;
            break;
        case 0x000F:
            VF = new_value;
            break;
        default:
            std::cout << "ATTENTION: NO VALID REGISTER FOR : "<< std::hex << std::setw(4) << std::setfill('0') << X << std::endl;
            throw CHIP_8_Emulator::CPU_Exception("Invalid Register Error");
            break;
    }
};

uint16_t Memory_Structure::read_address_register() const{
    return address_register;
}

//TODO: Validate
void Memory_Structure::set_address_register(uint16_t new_value) {
    address_register = new_value;
};


//TODO: Test, Validate
void Memory_Structure::increment_stack() {
    *mstack_pointer = (uint64_t) mprogram_counter + 2;
    mstack_pointer += 1;
};

//TODO: Test, Validate
void Memory_Structure::decrement_stack() {
    mstack_pointer -= 1;
    mprogram_counter = mmemory_chunk.data() + (*mstack_pointer);
};






































































