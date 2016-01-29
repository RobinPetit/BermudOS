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
add_executable(${PROJECT_NAME}.bin ${SOURCES})

add_subdirectory(kernel)
add_subdirectory(io)

#Add libraries
target_link_libraries(${PROJECT_NAME}.bin gcc kernel io)

#Make the iso:
file(COPY "${CMAKE_SOURCE_DIR}/boot/iso" DESTINATION "${CMAKE_BINARY_DIR}/boot")
#First, delete old iso
add_custom_command(TARGET ${PROJECT_NAME}.bin POST_BUILD COMMAND
	rm -f ${CMAKE_BINARY_DIR}/boot/iso/boot/${PROJECT_NAME}.iso)
#Then copy the executable
add_custom_command(TARGET ${PROJECT_NAME}.bin POST_BUILD COMMAND
	cp ${PROJECT_NAME}.bin ${CMAKE_BINARY_DIR}/boot/iso/boot/${PROJECT_NAME}.bin)
#Finaly create the iso with grub
add_custom_command(TARGET ${PROJECT_NAME}.bin POST_BUILD COMMAND
	grub-mkrescue -o ${PROJECT_NAME}.iso ${CMAKE_BINARY_DIR}/boot/iso)

