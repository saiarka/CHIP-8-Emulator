#ifndef EMULATOR_H_
#define EMULATOR_H_

#include "memory_structure.h"
#include "container.h"

#include <fstream>

class Emulator {
    
    Memory_Structure mMemory;
    SDL_Container mcontainer;

    uint8_t delay_timer;
    uint8_t sound_timer;

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

        //Helper Functions
        void reg_dump(uint16_t cur_inst , uint16_t add_reg_loc);
        void reg_load(uint16_t cur_inst, uint16_t add_reg_loc);
        

};

#endif
