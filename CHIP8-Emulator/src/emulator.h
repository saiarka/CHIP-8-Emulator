#ifndef EMULATOR_H_
#define EMULATOR_H_

#include "memory_structure.h"
#include <fstream>

class Emulator {
    
    Memory_Structure mMemory;


    public:
      
        Emulator(std::ifstream& rom_stream, int rom_size); //Init 
        ~Emulator(); //Destructor

        void decode();

        void execute();

        //TODO: OP code functions below: 


};

#endif
