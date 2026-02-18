
#include "emulator.h"
#include "emulator_exceptions.h"

#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>


Emulator::Emulator(std::ifstream& rom_stream, int rom_size) : 
    mMemory(rom_stream, rom_size), mcontainer(), waiting_for_key(false) {}

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


void Emulator::zero_instructions(uint16_t cur_inst) {
    switch(cur_inst) {
        case 0x00E0:
            SDL_SetRenderDrawColor(mcontainer.renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(mcontainer.renderer);
            std::fill(mcontainer.pixel_screen.begin(), mcontainer.pixel_screen.end(), 0);
            SDL_RenderPresent(mcontainer.renderer);
            break;
        case 0x00EE:
            mMemory.decrement_stack();
            break;
        default:
            throw CHIP_8_Emulator::CPU_Exception("Invalid OP CODE (Zero Instruction Failure)");
    }
}

void Emulator::one_instructions(uint16_t cur_inst) {
    //std::cout << "1NNN inst called\n";
    uint16_t address_to_jump = cur_inst & 0x0FFF;
    mMemory.jump_to_memory(address_to_jump);
}

void Emulator::two_instructions(uint16_t cur_inst) {
    uint16_t subroutine_location = cur_inst & 0x0FFF;
    mMemory.increment_stack();
    mMemory.jump_to_memory(subroutine_location);
}

void Emulator::three_instructions(uint16_t cur_inst) {
    uint8_t NN = (uint8_t)(cur_inst & 0x00FF);
    uint16_t X = (cur_inst & 0x0F00) >> 8; 
    uint8_t VX = mMemory.read_register_value(X);
    if (VX == NN) {
        mMemory.increment_program_counter();
    }
}

void Emulator::four_instructions(uint16_t cur_inst) {
    uint8_t NN = (uint8_t)(cur_inst & 0x00FF);
    uint16_t X = (cur_inst & 0x0F00) >> 8; 
    uint8_t VX = mMemory.read_register_value(X);
    if (VX != NN) {
        mMemory.increment_program_counter();
    }
}

void Emulator::five_instructions(uint16_t cur_inst) {
    uint16_t X = (cur_inst & 0x0F00) >> 8; 
    uint16_t Y = (cur_inst & 0x00F0) >> 4;
    uint8_t VX = mMemory.read_register_value(X);
    uint8_t VY = mMemory.read_register_value(Y);
    if (VX == VY) {
        mMemory.increment_program_counter();
    }
}

void Emulator::six_instructions(uint16_t cur_inst) {
    uint8_t NN = (uint8_t)(cur_inst & 0x00FF);
    uint16_t X = (cur_inst & 0x0F00) >> 8; 
    mMemory.set_register_value(X, NN);
}

void Emulator::seven_instructions(uint16_t cur_inst) {
    uint8_t NN = (cur_inst & 0x00FF);
    uint16_t X = (cur_inst & 0x0F00) >> 8;
    uint8_t VX = mMemory.read_register_value(X);
    uint8_t comb = (NN + VX);
    mMemory.set_register_value(X, comb);
}

void Emulator::eight_instructions(uint16_t cur_inst) {
    uint16_t flag = cur_inst & 0x000F;
    uint16_t X = (cur_inst & 0x0F00) >> 8;
    uint16_t Y = (cur_inst & 0x00F0) >> 4;
    uint8_t VX = mMemory.read_register_value(X);
    uint8_t VY = mMemory.read_register_value(Y);

    uint16_t big_sum;
    uint8_t is_overflow;
    uint8_t vx_difference;
    uint8_t underflow;
    uint8_t vy_difference;
    uint8_t most_sig_set;

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
            big_sum = static_cast<uint16_t>(VX) + static_cast<uint16_t>(VY);
            is_overflow = ((big_sum >> 8) != 0) ? 1 : 0;
            mMemory.set_register_value(X, VX + VY);
            mMemory.set_register_value(0x000F, is_overflow);
            break;
        case 0x0005:
            vx_difference = VX - VY;
            underflow = (VX >= VY) ? 1 : 0;
            mMemory.set_register_value(X, vx_difference);
            mMemory.set_register_value(0x000F, underflow);
            break;
        case 0x0006:
            //TODO: Variable instruction depending on arch. 
            most_sig_set = ((VX & 0b00000001) != 0) ? 1 : 0;
            mMemory.set_register_value(X, (VX >> 1));
            mMemory.set_register_value(0x000F, most_sig_set);
            break;
        case 0x0007:
            vy_difference = VY - VX;
            underflow = (VY >= VX) ? 1 : 0;
            mMemory.set_register_value(X, vy_difference);
            mMemory.set_register_value(0x000F, underflow);
            break;
        case 0x000E:
            most_sig_set = ((VX & 0b10000000) != 0) ? 1 : 0;
            mMemory.set_register_value(X, (VX << 1));
            mMemory.set_register_value(0x000F, most_sig_set);
            break;
        default:
            throw CHIP_8_Emulator::CPU_Exception("Invalid OP CODE (Failed 8 Instruction)");
    }
}

void Emulator::nine_instructions(uint16_t cur_inst) {
    uint16_t X = (cur_inst & 0x0F00) >> 8;
    uint16_t Y = (cur_inst & 0x00F0) >> 4;
    uint8_t VX = mMemory.read_register_value(X);
    uint8_t VY = mMemory.read_register_value(Y);
    if (VX != VY) {
        mMemory.increment_program_counter();
    }
}

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

//TODO : Optimize
void Emulator::thirteen_instructions(uint16_t cur_inst) {
    uint16_t X = (cur_inst & 0x0F00) >> 8;
    uint16_t Y = (cur_inst & 0x00F0) >> 4;
    uint16_t N = (cur_inst & 0x000F);
    uint8_t VX = mMemory.read_register_value(X) % mcontainer.SCREEN_WIDTH;
    uint8_t VY = mMemory.read_register_value(Y) % mcontainer.SCREEN_HEIGHT;
    uint16_t add_reg_loc = mMemory.read_address_register() & 0x0FFF;

    mMemory.set_register_value(0x000F, 0);
    int i = 0, j = 0;
    for (uint8_t row = VY; row < VY + N && row < mcontainer.SCREEN_HEIGHT; row++) {
        uint8_t mem_byte = mMemory.read_memory_at(add_reg_loc + i);
        i++;
        j = 0;
        for (uint8_t pixel = VX; pixel < VX + 8 && pixel < mcontainer.SCREEN_WIDTH; pixel++) {
            uint8_t cur_pix = mcontainer.pixel_screen[row * mcontainer.SCREEN_WIDTH + pixel];
            uint8_t new_pix = (mem_byte & (0x80 >> j)) >> (7 - j);
            j++;
            
            if (new_pix == 1) {
                uint8_t pixel_change = cur_pix ^ new_pix; 
                if (pixel_change == 0) {
                    mMemory.set_register_value(0x000F, 1);
                    SDL_SetRenderDrawColor(mcontainer.renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
                }else {
                    SDL_SetRenderDrawColor(mcontainer.renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
                }
                mcontainer.pixel_screen[row * mcontainer.SCREEN_WIDTH + pixel] = pixel_change;
                SDL_RenderPoint(mcontainer.renderer, pixel, row);
            }
        }
    }
}

void Emulator::fourteen_instructions(uint16_t cur_inst) {
    const uint16_t X = (cur_inst & 0x0F00) >> 8;
    const uint16_t cond = (cur_inst & 0x00FF);
    const uint8_t key = mMemory.read_register_value(X) & 0x0F;
    const SDL_Scancode code = get_scancode_from_key(key);
    switch(cond) {
        case 0x009E:
            check_key(code, 1);
            break;
        case 0x00A1:
            check_key(code, 0);
            break;
    }
}

void Emulator::check_key(const SDL_Scancode code, const bool want_pressed) {
    const bool* keyboard_states = SDL_GetKeyboardState(nullptr);
    if (keyboard_states[code] && want_pressed || keyboard_states[code] ^ (!want_pressed)) {
        mMemory.mprogram_counter += 2;
    }
}


const SDL_Scancode Emulator::get_scancode_from_key(const uint8_t key) {
    switch(key) {
        case 0x00:
            return SDL_SCANCODE_X;
            break;
        case 0x01:
            return SDL_SCANCODE_1;
            break;
        case 0x02:
            return SDL_SCANCODE_2;
            break;
        case 0x03:
            return SDL_SCANCODE_3;
            break;
        case 0x04:
            return SDL_SCANCODE_Q;
            break;
        case 0x05:
            return SDL_SCANCODE_W;
            break;
        case 0x06:
            return SDL_SCANCODE_E;
            break;
        case 0x07:
            return SDL_SCANCODE_A;
            break;
        case 0x08:
            return SDL_SCANCODE_S;
            break;
        case 0x09:
            return SDL_SCANCODE_D;
            break;
        case 0x0A:
            return SDL_SCANCODE_Z;
            break;
        case 0x0B:
            return SDL_SCANCODE_C;
            break;
        case 0x0C:
            return SDL_SCANCODE_4;
            break;
        case 0x0D:
            return SDL_SCANCODE_R;
            break;
        case 0x0E:
            return SDL_SCANCODE_F;
            break;
        case 0x0F:
            return SDL_SCANCODE_V;
            break;
        default:
            throw CHIP_8_Emulator::CPU_Exception("Invalid Key for Scancode");
            break;
    }
}


//TODO : Implement instruction functions
void Emulator::fifteen_instructions(uint16_t cur_inst) {
    uint16_t detail = cur_inst & 0x00FF;
    uint16_t X = (cur_inst & 0x0F00) >> 8;
    uint16_t VX = mMemory.read_register_value(X);
    uint16_t add_reg = mMemory.read_address_register();
    uint16_t add_reg_loc = add_reg & 0x0FFF; 
    if (add_reg_loc > 4096 || add_reg_loc < 0) { throw CHIP_8_Emulator::CPU_Exception("Invalid address reg loc! (fifteen_inst)");}

    //BCD Calc
    uint8_t ones_digit;
    uint8_t tens_digit; 
    uint8_t hundreds_digit;

    switch(detail) {
        case 0x0007:
            break;
        case 0x000A:
            waiting_for_key = true;
            key_val = X;
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
            ones_digit = (VX % 10);
            tens_digit = ((VX / 10) % 10);
            hundreds_digit = (VX / 100); 
            mMemory.mmemory_chunk[add_reg_loc] = hundreds_digit;
            mMemory.mmemory_chunk[add_reg_loc + 1] = tens_digit;
            mMemory.mmemory_chunk[add_reg_loc + 2] = ones_digit;
            break;
        case 0x0055:
            reg_dump(cur_inst, add_reg_loc);
            break;
        case 0x0065:
            reg_load(cur_inst, add_reg_loc);
            break;
    }
}

void Emulator::handle_key_press(const SDL_Event& e) {
    waiting_for_key = false;
    switch(e.key.scancode) {
        case SDL_SCANCODE_X:
            mMemory.set_register_value(key_val, 0);
        case SDL_SCANCODE_1:
            mMemory.set_register_value(key_val, 1);
        case SDL_SCANCODE_2:
            mMemory.set_register_value(key_val, 2);
        case SDL_SCANCODE_3:
            mMemory.set_register_value(key_val, 3);
        case SDL_SCANCODE_Q:
            mMemory.set_register_value(key_val, 4);
        case SDL_SCANCODE_W:
            mMemory.set_register_value(key_val, 5);
        case SDL_SCANCODE_E:
            mMemory.set_register_value(key_val, 6);
        case SDL_SCANCODE_A:
            mMemory.set_register_value(key_val, 7);
        case SDL_SCANCODE_S:
            mMemory.set_register_value(key_val, 8);
        case SDL_SCANCODE_D:
            mMemory.set_register_value(key_val, 9);
        case SDL_SCANCODE_Z:
            mMemory.set_register_value(key_val, 0xA);
        case SDL_SCANCODE_C:
            mMemory.set_register_value(key_val, 0xB);
        case SDL_SCANCODE_4:
            mMemory.set_register_value(key_val, 0xC);
        case SDL_SCANCODE_R:
            mMemory.set_register_value(key_val, 0xD);
        case SDL_SCANCODE_F:
            mMemory.set_register_value(key_val, 0xE);
        case SDL_SCANCODE_V:
            mMemory.set_register_value(key_val, 0xF);
        default:
            waiting_for_key = true;
    }
}

void Emulator::reg_dump(uint16_t cur_inst, uint16_t add_reg_loc) {
    uint16_t X = (cur_inst & 0x0F00) >> 8;
    if (add_reg_loc + X > 4096) { throw CHIP_8_Emulator::CPU_Exception("reg_dump exceeds memory capacity!");}
    for (uint16_t i = 0; i <= X; i++) {
        uint8_t VX = mMemory.read_register_value(i);
        mMemory.mmemory_chunk[add_reg_loc + i] = VX;
    }
}

void Emulator::reg_load(uint16_t cur_inst, uint16_t add_reg_loc) {
    uint16_t X = (cur_inst & 0x0F00) >> 8;
    if (add_reg_loc + X > 4096) { throw CHIP_8_Emulator::CPU_Exception("reg_load exceeds memory capacity!");}
    for (uint16_t i = 0; i <= X; i++) {
        uint8_t load_val = mMemory.read_memory_at(add_reg_loc+i);
        mMemory.set_register_value(i, load_val);
    }
}








































