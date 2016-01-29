cmake_minimum_required(VERSION 3.2)

project(BermudOS LANGUAGES C ASM_NASM)

#Set up the C compiler
set(CMAKE_C_COMPILER "i686-elf-gcc")
set(CMAKE_C_FLAGS "-std=gnu99 -ffreestanding -O2")

#Set up the linker
set(LINKER_FILE "boot/linker.ld")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS}  -nostdlib -T ${LINKER_FILE}")
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS>
<LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

set(C_SOURCES "boot/kernel.c")
set(ASM_SOURCES "boot/boot.asm")

#Create the main executable
add_executable(${PROJECT_NAME}.bin ${C_SOURCES} ${ASM_SOURCES})

add_subdirectory(kernel)
add_subdirectory(io)

#Add libraries
target_link_libraries(${PROJECT_NAME}.bin gcc kernel io)

