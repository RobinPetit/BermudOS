CC=i686-elf-gcc
C_FLAGS=-std=gnu99 -ffreestanding -O2 -I ../include/BermudOS
C_FLAGS_WARNING=-Wall -Wextra
C_FILES=$(wildcard **/*.c)
OBJECTS=$(patsubst %.c, obj/%.o, $(C_FILES))

CC: $(OBJECTS)

obj/%.o: %.c
	$(CC) -c $< -o $@ $(C_FLAGS) $(C_FLAGS_WARNING)

clean:
	rm -f $(OBJECTS)
