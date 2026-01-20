
#include "emulator.h"
#include <iostream>


Emulator::Emulator(std::ifstream& rom_stream, int rom_size) : 
    mMemory(rom_stream, rom_size){};


//Output used by decode_execute to find and execute relevant op code
//TODO: Needless abstraction? Look into 
uint16_t Emulator::fetch() {
    uint16_t instr = mMemory.get_current_instruction();
    return instr;
}


void Emulator::decode_execute() {
    
    //Get 'first-byte' of relevant instruction
    uint16_t current_instruction = fetch();
    uint8_t first_code = current_instruction >> 12;

    //TODO: Temporary code for copy-paste, remove later
    uint8_t second_code = (current_instruction >> 8) & 0x0F;
    uint8_t third_code = (current_instruction & 0x00F0) >> 4;
    uint8_t fourth_code = (current_instruction & 0x000F);

    switch(first_code) {
        case 0x0:
            zero_instructions(current_instruction);
        case 0x1:
            one_instructions(current_instruction);
        case 0x2:
            two_instructions(current_instruction);
        case 0x3:
            three_instructions(current_instruction);
        case 0x4:
            four_instructions(current_instruction);
        case 0x5:
            five_instructions(current_instruction);
        case 0x6:
            six_instructions(current_instruction);
        case 0x7:
            seven_instructions(current_instruction);
        case 0x8:
            eight_instructions(current_instruction);
        case 0x9:
            nine_instructions(current_instruction);
        case 0xA:
            ten_instructions(current_instruction);
        case 0xB:
            eleven_instructions(current_instruction);
        case 0xC:
            twelve_instructions(current_instruction);
        case 0xD:
            thirteen_instructions(current_instruction);
        case 0xE:
            fourteen_instructions(current_instruction);
        case 0xF:
            fifteen_instructions(current_instruction);
        default:
            std::cout << "Invalid OP Code ERROR" << std::endl;
            break;
    }
}


//TODO : Implement instruction functions
void Emulator::zero_instructions(uint16_t cur_inst) {

    return;
}

//TODO: Test
void Emulator::one_instructions(uint16_t cur_inst) {

    uint16_t address_to_jump = cur_inst & 0x0FFF;
    mMemory.jump_to_memory(address_to_jump);

    return;
}

//TODO : Implement instruction functions
void Emulator::two_instructions(uint16_t cur_inst) {

    return;
}
//TODO : Implement instruction functions
void Emulator::three_instructions(uint16_t cur_inst) {

    uint16_t NN = cur_inst & 0x00FF;
    uint16_t X = (cur_inst & 0x0F00) >> 8; 

    return;
}
//TODO : Implement instruction functions
void Emulator::four_instructions(uint16_t cur_inst) {

    return;
}
//TODO : Implement instruction functions
void Emulator::five_instructions(uint16_t cur_inst) {

    return;
}
//TODO : Implement instruction functions
void Emulator::six_instructions(uint16_t cur_inst) {

    return;
}
//TODO : Implement instruction functions
void Emulator::seven_instructions(uint16_t cur_inst) {

    return;
}
//TODO : Implement instruction functions
void Emulator::eight_instructions(uint16_t cur_inst) {

    return;
}
//TODO : Implement instruction functions
void Emulator::nine_instructions(uint16_t cur_inst) {

    return;
}
//TODO : Implement instruction functions
void Emulator::ten_instructions(uint16_t cur_inst) {

    return;
}
//TODO : Implement instruction functions
void Emulator::eleven_instructions(uint16_t cur_inst) {

    return;
}
//TODO : Implement instruction functions
void Emulator::twelve_instructions(uint16_t cur_inst) {

    return;
}
//TODO : Implement instruction functions
void Emulator::thirteen_instructions(uint16_t cur_inst) {

    return;
}
//TODO : Implement instruction functions
void Emulator::fourteen_instructions(uint16_t cur_inst) {

    return;
}
//TODO : Implement instruction functions
void Emulator::fifteen_instructions(uint16_t cur_inst) {
    return;
}








































