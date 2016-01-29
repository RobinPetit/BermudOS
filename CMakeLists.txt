cmake_minimum_required(VERSION 3.2)

set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")

project(BermudOS LANGUAGES C ASM_NASM)

#Set up the C compiler
set(CMAKE_C_COMPILER "i686-elf-gcc")
set(CMAKE_C_FLAGS "-std=gnu99 -ffreestanding -O2")

#Set up the linker
set(LINKER_FILE "${PROJECT_SOURCE_DIR}/boot/linker.ld")
set(CMAKE_C_LINK_FLAGS "-nostdlib -T ${LINKER_FILE}")
#Some flags are set by default; disable them
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

#List the main executable source files
set(SOURCES
	"boot/kernel.c"
	"boot/boot.asm"
	)

#Create the main executable
add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(kernel)
add_subdirectory(io)

#Add libraries
target_link_libraries(${PROJECT_NAME} gcc kernel io)

