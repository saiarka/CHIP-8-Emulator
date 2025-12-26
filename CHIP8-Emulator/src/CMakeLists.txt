# CMakeList.txt : CMake project for CHIP8-Emulator, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_library(Chip_Lib "emulator.cpp" "memory_structure.cpp")
add_executable (CHIP8-Emulator "main.cpp")

target_link_libraries(CHIP8-Emulator PRIVATE SDL3::SDL3 Chip_Lib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CHIP8-Emulator PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
