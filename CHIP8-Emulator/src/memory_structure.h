#ifndef MEMORY_STRUCTURE_H_
#define MEMORY_STRUCTURE_H_

#include<memory>
#include <cstdint>
#include <vector>

class Memory_Structure {

    //Stack
    //Also acts as base pointer
    std::vector<uint8_t> mstack_chunk;

    //Stack Pointer
    uint8_t* mstack_pointer;
    
    //Code Chunk
    std::vector<uint8_t> mmemory_chunk;
    
    //Program Counter used to iterate through code chunk data
    uint8_t* mprogram_counter;

    //Registers
    int16_t V0;
    int16_t V1;
    int16_t V2;
    int16_t V3;
    int16_t V4;
    int16_t V5;
    int16_t V6;
    int16_t V7;
    int16_t V8;
    int16_t V9;
    int16_t VA;
    int16_t VB;
    int16_t VC;
    int16_t VD;
    int16_t VE;
    int16_t VF;

   
    public:

        Memory_Structure(std::ifstream& rom_stream, int data_length);
        ~Memory_Structure();

        void print_memory(); //Test function for checking memory
                             
        uint16_t get_current_instruction();

        void increment_program_counter();

        void jump_to_memory(uint16_t memory_address);

        uint16_t read_register_value(uint16_t X);


};




#endif

