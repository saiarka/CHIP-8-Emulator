#ifndef EMULATOR_H_
#define EMULATOR_H_

#include "memory_structure.h"
#include <fstream>

class Emulator {
    
    Memory_Structure mMemory;


    public:
      
        Emulator(std::ifstream& rom_stream, int rom_size); //Init 
        ~Emulator() = default; //Destructor
        
        uint16_t fetch();

        void decode_execute();

        void zero_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        void one_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        void two_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        void three_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        void four_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        void five_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        void six_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        void seven_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        void eight_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        void nine_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        void ten_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        void eleven_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        void twelve_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        void thirteen_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        void fourteen_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        void fifteen_instructions(uint8_t first_code, uint8_t second_code, uint8_t third_code, uint8_t fourth_code);
        
        



};

#endif
