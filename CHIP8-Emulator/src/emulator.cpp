
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
    uint8_t second_code = (current_instruction >> 8) & 0x0F;
    uint8_t third_code = (current_instruction & 0x00F0) >> 4;
    uint8_t fourth_code = (current_instruction & 0x000F);

    switch(first_code) {
        case 0x0:
            zero_instructions(first_code, second_code, third_code, fourth_code);
        case 0x1:
            one_instructions(first_code, second_code, third_code, fourth_code);
        case 0x2:
            two_instructions(first_code, second_code, third_code, fourth_code);
        case 0x3:
            three_instructions(first_code, second_code, third_code, fourth_code);
        case 0x4:
            four_instructions(first_code, second_code, third_code, fourth_code);
        case 0x5:
            five_instructions(first_code, second_code, third_code, fourth_code);
        case 0x6:
            six_instructions(first_code, second_code, third_code, fourth_code);
        case 0x7:
            seven_instructions(first_code, second_code, third_code, fourth_code);
        case 0x8:
            eight_instructions(first_code, second_code, third_code, fourth_code);
        case 0x9:
            nine_instructions(first_code, second_code, third_code, fourth_code);
        case 0xA:
            ten_instructions(first_code, second_code, third_code, fourth_code);
        case 0xB:
            eleven_instructions(first_code, second_code, third_code, fourth_code);
        case 0xC:
            twelve_instructions(first_code, second_code, third_code, fourth_code);
        case 0xD:
            thirteen_instructions(first_code, second_code, third_code, fourth_code);
        case 0xE:
            fourteen_instructions(first_code, second_code, third_code, fourth_code);
        case 0xF:
            fifteen_instructions(first_code, second_code, third_code, fourth_code);
        default:
            std::cout << "Invalid OP Code ERROR" << std::endl;
            break;
    }
}





