CC = riscv64-unknown-elf-gcc
CFLAGS =  -nostdlib -ffreestanding -mcmodel=medany -march=rv32ima -mabi=ilp32 -g -Wall -w -D CONFIG_SYSCALL

OBJ = $(wildcard *.c) $(wildcard *.h) $(wildcard *.S)

os.elf: $(OBJ)
	$(CC) $(CFLAGS) -T linker.ld -o os.elf $^

clean:
	rm -f *.elf *.img
