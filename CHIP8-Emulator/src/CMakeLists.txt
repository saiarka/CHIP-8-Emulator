
add_library(Chip_Lib "emulator.cpp" "memory_structure.cpp" "container.cpp")

target_link_libraries(Chip_Lib PRIVATE SDL3::SDL3)

add_executable (CHIP8-Emulator "main.cpp") 

target_link_libraries(CHIP8-Emulator PRIVATE SDL3::SDL3 Chip_Lib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CHIP8-Emulator PROPERTY CXX_STANDARD 20)
endif()

