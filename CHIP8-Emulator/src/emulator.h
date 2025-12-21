#ifndef EMULATOR_H_
#define EMULATOR_H_

#include "memory_structure.h"

class Emulator {
    
    Memory_Structure mMemory;

    public:
      
        Emulator(); //Init 
        ~Emulator(); //Destructor

        
        //TODO: Rom input param 
        void read_in_rom();

        void decode();

        //TODO: OP code functions below: 


};

#endif
