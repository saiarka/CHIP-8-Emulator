#ifndef MEMORY_STRUCTURE_H_
#define MEMORY_STRUCTURE_H_

#include <memory>
#include <cstdint>
#include <vector>

class Memory_Structure {

    //Stack
    //Also acts as base pointer
    std::vector<uint64_t> mstack_chunk;

    //Stack Pointer
    uint64_t* mstack_pointer;
    
    //Code Chunk
    std::vector<uint8_t> mmemory_chunk;
    
    //Program Counter used to iterate through code chunk data
    uint8_t* mprogram_counter;

    //Registers
    uint8_t V0;
    uint8_t V1;
    uint8_t V2;
    uint8_t V3;
    uint8_t V4;
    uint8_t V5;
    uint8_t V6;
    uint8_t V7;
    uint8_t V8;
    uint8_t V9;
    uint8_t VA;
    uint8_t VB;
    uint8_t VC;
    uint8_t VD;
    uint8_t VE;
    uint8_t VF;

    uint16_t address_register;

    //Timers -- Checked and Changed in main emulation loop
    uint8_t delay_timer;
    uint8_t sound_timer;
   
    public:

        Memory_Structure(std::ifstream& rom_stream, int data_length);
        ~Memory_Structure();

        void print_memory(); //Test function for checking memory
                             
        uint16_t get_current_instruction();
        void increment_program_counter();

        void jump_to_memory(uint16_t memory_address);
        void set_memory_at(uint16_t memory_address, uint16_t new_memory);
        uint8_t read_memory_at(uint16_t memory_address) const;

        uint8_t read_register_value(uint16_t X) const;
        uint16_t read_address_register() const;
        void set_register_value(uint16_t X, uint8_t new_value);
        void set_address_register(uint16_t new_value);

        void increment_stack();
        void decrement_stack();


};




#endif

