CC=i686-elf-gcc
C_FLAGS=-std=gnu99 -ffreestanding -O2 -I ../include/BermudOS
C_FLAGS_WARNING=-Wall -Wextra
C_FILES=$(wildcard **/*.c) $(wildcard *.c)
C_OBJ=$(patsubst %.c, obj/%.o, $(C_FILES))

kernel: $(C_OBJ)

obj/%.o: %.c
	$(CC) -c $< -o $@ $(C_FLAGS) $(C_FLAGS_WARNING)

clean:
	rm -f $(C_OBJ)
