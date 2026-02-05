
#include "emulator.h"
#include "emulator_exceptions.h"
#include <iostream>
#include <random>


Emulator::Emulator(std::ifstream& rom_stream, int rom_size) : 
    mMemory(rom_stream, rom_size), mcontainer() {}


//Output used by decode_execute to find and execute relevant op code
//TODO: Needless abstraction? Look into 
uint16_t Emulator::fetch() {
    uint16_t instr = mMemory.get_current_instruction();
    return instr;
}

//TODO: Test
void Emulator::decode_execute() {
    
    //Get 'first-byte' of relevant instruction
    uint16_t current_instruction = fetch();
    uint16_t first_code = current_instruction >> 12;

    switch(first_code) {
        case 0x0:
            zero_instructions(current_instruction);
            break;
        case 0x1:
            one_instructions(current_instruction);
            break;
        case 0x2:
            two_instructions(current_instruction);
            break;
        case 0x3:
            three_instructions(current_instruction);
            break;
        case 0x4:
            four_instructions(current_instruction);
            break;
        case 0x5:
            five_instructions(current_instruction);
            break;
        case 0x6:
            six_instructions(current_instruction);
            break;
        case 0x7:
            seven_instructions(current_instruction);
            break;
        case 0x8:
            eight_instructions(current_instruction);
            break;
        case 0x9:
            nine_instructions(current_instruction);
            break;
        case 0xA:
            ten_instructions(current_instruction);
            break;
        case 0xB:
            eleven_instructions(current_instruction);
            break;
        case 0xC:
            twelve_instructions(current_instruction);
            break;
        case 0xD:
            thirteen_instructions(current_instruction);
            break;
        case 0xE:
            fourteen_instructions(current_instruction);
            break;
        case 0xF:
            fifteen_instructions(current_instruction);
            break;
        default:
            throw CHIP_8_Emulator::CPU_Exception("Invalid OP CODE (First 4 bits)");
            break;
    }
}


//TODO : Test
void Emulator::zero_instructions(uint16_t cur_inst) {
    switch(cur_inst) {
        case 0x00E0:
            std::cout << "0x00EO inst called" << std::endl;
            SDL_SetRenderDrawColor(mcontainer.renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(mcontainer.renderer);
            SDL_RenderPresent(mcontainer.renderer);
            break;
        case 0x00EE:
            std::cout << "0x00EE inst called" << std::endl;
            mMemory.decrement_stack();
            break;
        default:
            throw CHIP_8_Emulator::CPU_Exception("Invalid OP CODE (Zero Instruction Failure)");
    }
}

//TODO: Test
void Emulator::one_instructions(uint16_t cur_inst) {
    uint16_t address_to_jump = cur_inst & 0x0FFF;
    mMemory.jump_to_memory(address_to_jump);
}

//TODO : Test 
void Emulator::two_instructions(uint16_t cur_inst) {
    uint16_t subroutine_location = cur_inst & 0x0FFF;
    mMemory.increment_stack();
    mMemory.jump_to_memory(subroutine_location);
}

//TODO : Test 
void Emulator::three_instructions(uint16_t cur_inst) {
    uint8_t NN = (uint8_t)(cur_inst & 0x00FF);
    uint16_t X = (cur_inst & 0x0F00) >> 8; 
    uint8_t register_value = mMemory.read_register_value(X);
    if (register_value == NN) {
        mMemory.increment_program_counter();
    }
}

//TODO : Test
void Emulator::four_instructions(uint16_t cur_inst) {
    uint8_t NN = (uint8_t)(cur_inst & 0x00FF);
    uint16_t X = (cur_inst & 0x0F00) >> 8; 
    uint8_t register_value = mMemory.read_register_value(X);
    if (register_value != NN) {
        mMemory.increment_program_counter();
    }
}
//TODO : Test 
void Emulator::five_instructions(uint16_t cur_inst) {
    uint16_t X = (cur_inst & 0x0F00) >> 8; 
    uint16_t Y = (cur_inst & 0x00F0) >> 4;
    uint8_t VX = mMemory.read_register_value(X);
    uint8_t VY = mMemory.read_register_value(Y);
    if (VX == VY) {
        mMemory.increment_program_counter();
    }
}
//TODO : Test 
void Emulator::six_instructions(uint16_t cur_inst) {
    uint8_t NN = (uint8_t)(cur_inst & 0x00FF);
    uint16_t X = (cur_inst & 0x0F00) >> 8; 
    mMemory.set_register_value(X, NN);
}

//TODO : Test
//Ensure carry flag not changed
void Emulator::seven_instructions(uint16_t cur_inst) {
    uint16_t NN = (cur_inst & 0x00FF);
    uint16_t X = (cur_inst & 0x0F00) >> 8; 
    uint8_t comb = (uint8_t)(NN + X);
    mMemory.set_register_value(X, comb);
    
    return;
}
//TODO : Test 
//Optimize? Many calculations per inst --> Seperate into functions
void Emulator::eight_instructions(uint16_t cur_inst) {

    uint16_t flag = cur_inst & 0x000F;
    uint16_t X = (cur_inst & 0x0F00) >> 8;
    uint16_t Y = (cur_inst & 0x00F0) >> 4;
    uint8_t VX = mMemory.read_register_value(X);
    uint8_t VY = mMemory.read_register_value(Y);

    uint16_t big_sum = (uint16_t)VX + (uint16_t)VY;
    uint8_t vx_difference = VX - VY;
    uint8_t vy_difference = VY - VX;
    uint8_t is_overflow = ((big_sum >> 8) != 1) ? 1 : 0;
    uint8_t five_underflow = (VX >= VY) ? 1 : 0;
    uint8_t seven_underflow = (VY >= VX) ? 1 : 0;
    uint8_t most_sig_set = ((VX & 0b10000000) != 0) ? 1 : 0;

    switch(flag) {
        case 0x0000:
            mMemory.set_register_value(X, VY);
            break;
        case 0x0001:
            mMemory.set_register_value(X, VX | VY);
            break;
        case 0x0002:
            mMemory.set_register_value(X, VX & VY);
            break;
        case 0x0003:
            mMemory.set_register_value(X, VX ^ VY);
            break;
        case 0x0004:
            mMemory.set_register_value(X, (uint8_t)big_sum);
            mMemory.set_register_value(0x000F, is_overflow);
            break;
        case 0x0005:
            mMemory.set_register_value(X, vx_difference);
            mMemory.set_register_value(0x000F, five_underflow);
            break;
        case 0x0006:
            mMemory.set_register_value(0x000F, (VX & 0x0F));
            mMemory.set_register_value(X, (VX >> 1));
            break;
        case 0x0007:
            mMemory.set_register_value(X, vy_difference);
            mMemory.set_register_value(0x000F, seven_underflow);
            break;
        case 0x000E:
            mMemory.set_register_value(X, (VX << 1));
            mMemory.set_register_value(0x000F, most_sig_set);
            break;
        default:
            throw CHIP_8_Emulator::CPU_Exception("Invalid OP CODE (Failed 8 Instruction)");
    }
}
//TODO : Test 
void Emulator::nine_instructions(uint16_t cur_inst) {
    uint16_t X = (cur_inst & 0x0F00) >> 8;
    uint16_t Y = (cur_inst & 0x00F0) >> 4;
    uint8_t VX = mMemory.read_register_value(X);
    uint8_t VY = mMemory.read_register_value(Y);

    if (VX != VY) {
        mMemory.increment_program_counter();
    }
}

//TODO : Test 
void Emulator::ten_instructions(uint16_t cur_inst) {
    uint16_t NNN = (cur_inst & 0x0FFF);
    mMemory.set_address_register(NNN);
}

//TODO : Test 
void Emulator::eleven_instructions(uint16_t cur_inst) {
    uint8_t V0 = mMemory.read_register_value(0x0000);
    uint16_t NNN = (cur_inst & 0x0FFF);
    mMemory.jump_to_memory(NNN + (uint16_t)V0);
}

//TODO : Test 
void Emulator::twelve_instructions(uint16_t cur_inst) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 255);
    int random = dist(rd);
    uint16_t NN = cur_inst & 0x00FF;
    uint16_t X = (cur_inst & 0x0F00) >> 8;
    mMemory.set_register_value(X, NN & random);
}

//TODO : Test, Validate 
//Notes:
//  - If VX and VY are max 8 bit values, max x and y are 0-255?
//  - Assumes N is not zero
void Emulator::thirteen_instructions(uint16_t cur_inst) {

    uint16_t X = (cur_inst & 0x0F00) >> 8;
    uint16_t Y = (cur_inst & 0x00F0) >> 4;
    uint16_t N = (cur_inst & 0x000F);
    uint8_t VX = mMemory.read_register_value(X) % mcontainer.SCREEN_WIDTH;
    uint8_t VY = mMemory.read_register_value(Y) % mcontainer.SCREEN_WIDTH;
    uint16_t add_reg_loc = mMemory.read_address_register() & 0x0FFF;
    mMemory.set_register_value(0x000F, 0);
    
    for (int i = 0; i < N; i++) {
        if (VY + N > mcontainer.SCREEN_HEIGHT) {return;}

        uint8_t memory_byte = mMemory.read_memory_at(add_reg_loc + i);
        uint8_t pixel_byte = mcontainer.pixel_screen[(VY+N) * mcontainer.SCREEN_WIDTH + VX];
        uint8_t byte_diff = memory_byte ^ pixel_byte; 
        if ((byte_diff & memory_byte) != memory_byte & mMemory.read_register_value(0x000F) != 1) {
            mMemory.set_register_value(0x000F, 1);
        }

        mcontainer.pixel_screen[(VY+N) * mcontainer.SCREEN_WIDTH + VX] = byte_diff;
        SDL_RenderClear(mcontainer.renderer);
        for (int j = 0; j < 8; j++) {
            if (VX + i > mcontainer.SCREEN_WIDTH) {continue;}

            if (mcontainer.pixel_screen[(VY+N) * 256 + (VX + j)] & (0x80 >> j)) {
                SDL_SetRenderDrawColor(mcontainer.renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
            }else {
                SDL_SetRenderDrawColor(mcontainer.renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
            }
            SDL_RenderPoint(mcontainer.renderer, VX + j, VY + i);
        }
    }
}

//TODO : Implement instruction functions
void Emulator::fourteen_instructions(uint16_t cur_inst) {

    return;
}
//TODO : Implement instruction functions
void Emulator::fifteen_instructions(uint16_t cur_inst) {

    uint16_t detail = cur_inst & 0x00FF;
    uint16_t VX = mMemory.read_register_value((cur_inst & 0x0F00) >> 8);
    uint16_t add_reg = mMemory.read_address_register();
    uint16_t add_reg_loc = add_reg & 0x0FFF; 
    if (add_reg_loc > 4096 || add_reg_loc < 4096) { throw CHIP_8_Emulator::CPU_Exception("Invalid address reg loc! (fifteen_inst)");}

    //BCD Calc
    uint16_t ones_digit = (VX % 10);
    uint16_t tens_digit = ((VX / 10) % 10) * 10;
    uint16_t hundreds_digit = (VX / 100) * 100; 

    switch(detail) {
        case 0x0007:
            break;
        case 0x000A:
            break;
        case 0x0015:
            break;
        case 0x0018:
            break;
        case 0x001E:
            mMemory.set_address_register(VX + add_reg);
            break;
        case 0x0029:
            break;
        case 0x0033:
            mMemory.set_memory_at(add_reg_loc, hundreds_digit);
            mMemory.set_memory_at(add_reg_loc+1, hundreds_digit);
            mMemory.set_memory_at(add_reg_loc+2, hundreds_digit);
            break;
        case 0x0055:
            reg_dump(cur_inst, add_reg_loc);
            break;
        case 0x0065:
            reg_load(cur_inst, add_reg_loc);
            break;
        default:
            throw CHIP_8_Emulator::CPU_Exception("Invalid OP CODE (Failed F Instruction)");
    }
}


//TODO: Test
void Emulator::reg_dump(uint16_t cur_inst, uint16_t add_reg_loc) {
    uint16_t X = (cur_inst & 0x0F00) >> 8;
    if (add_reg_loc + X > 4096) { throw CHIP_8_Emulator::CPU_Exception("reg_dump exceeds memory capacity!");}
    for (uint16_t i = 0; i <= X; i++) {
        uint8_t VX = mMemory.read_register_value(i);
        mMemory.set_memory_at(add_reg_loc + i, VX);
    }
}

//TODO: Test
void Emulator::reg_load(uint16_t cur_inst, uint16_t add_reg_loc) {
    uint16_t X = (cur_inst & 0x0F00) >> 8;
    if (add_reg_loc + X > 4096) { throw CHIP_8_Emulator::CPU_Exception("reg_dump exceeds memory capacity!");}
    for (uint16_t i = 0; i <= X; i++) {
        uint8_t load_val = mMemory.read_memory_at(add_reg_loc+i);
        mMemory.set_register_value(X, load_val);
    }
}








































