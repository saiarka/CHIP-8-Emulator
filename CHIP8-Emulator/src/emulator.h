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

        void zero_instructions(uint16_t cur_inst);
        void one_instructions(uint16_t cur_inst);
        void two_instructions(uint16_t cur_inst);
        void three_instructions(uint16_t cur_inst);
        void four_instructions(uint16_t cur_inst);
        void five_instructions(uint16_t cur_inst);
        void six_instructions(uint16_t cur_inst);
        void seven_instructions(uint16_t cur_inst);
        void eight_instructions(uint16_t cur_inst);
        void nine_instructions(uint16_t cur_inst);
        void ten_instructions(uint16_t cur_inst);
        void eleven_instructions(uint16_t cur_inst);
        void twelve_instructions(uint16_t cur_inst);
        void thirteen_instructions(uint16_t cur_inst);
        void fourteen_instructions(uint16_t cur_inst);
        void fifteen_instructions(uint16_t cur_inst);
        

};

#endif
