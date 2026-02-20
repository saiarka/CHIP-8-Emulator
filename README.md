# CHIP-8-Emulator

This is a repository for a CHIP-8 Emulator built in C++17. CHIP-8 is an interpreter used in the 1970's to simplify game programming across different machines. Any machine with 
a CHIP-8 interpreter and respective program could run a CHIP-8 game. 

## Demos

## How to Run

## Technical Details

Understanding the underlying hardware of computer systems and how programming paradigms utilize said hardware has always been a fascinating subject to me. To understand it further, I've 
tried my hand at creating a CHIP-8 Emulator to 'emulate' the functionality of the CHIP-8 Interpreter. Effectively, the program will run through a given ROM (Read-Only-Memory) file and interpret the 
bytes as CHIP-8 instructions, much like how a computer might take in binary code and execute instructions on the CPU.

What this means is that my program has to emulate certain features of the original 'hardware'. A non-comprehensive list includes:
- CPU w/ Fetch, Decode, and Execute loop for all CHIP-8 Instructions 
- 4096 bytes of memory
- Program Counter
- 16 layer Call Stack
- Registers
- Graphics

Much of the meat of this project is in deciphering the ambigious instruction commands for the CPU. These instructions are prone to error as they typically incur some small side effects in memory which
left unattended can break the entire program. Rushing the implementation of even the simpliest instruction can lead to days of frustrating debugging. Weeding through line by line instructions in GDB and 
analyzing hexadecimal codes took me back to my second year OS class. Needless to say, this project has forced me to be more patient and detail-oriented. 

All that said, there's a lot of joy to be found in seeing a bunch of numbers and capital letters turn into Tetris with a press of a button (or the enter of a ./ command?). I learned so much about memory allocation,
game loop rendering, and overall C++ project organization through this project. If anyone's interested in these topics, I highly reccomend they go through with making an emulator themselves. 

## Planned Improvements

My MVP for this project was that it was able to 1. Run all of Timendus' ROM tests (Listed in Sources and Credits) and 2. For it to run at least 1 game.

However there are still a lot of improvements to be made. I want it to be able to run more games. I want the drawing to be less buggy. I'd like a more visually friendly interface for the emulator itself and perhaps more customization. 
I will include a more comprehensive list of details and bugs here in the future to be fixed. 

## Sources and Credits

https://github.com/Timendus/chip8-test-suite?tab=readme-ov-file

https://web.archive.org/web/20140825173007/http://vanbeveren.byethost13.com/stuff/CHIP8.pdf

https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#fetchdecodeexecute-loop
