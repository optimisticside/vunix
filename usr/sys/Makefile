CC = riscv64-unknown-elf-gcc
QEMU = qemu-system-riscv64
CFLAGS =  -nostdlib -ffreestanding -mcmodel=medany -march=rv32ima -mabi=ilp32 -g -Wall -w -D CONFIG_SYSCALL

OBJ = $(wildcard *.c) $(wildcard *.h) $(wildcard *.S)

os.elf: $(OBJ)
	$(CC) $(CFLAGS) -T linker.ld -o vunix.elf $^

qemu: os.elf
	$(QEMU) -kernel vunix.elf -serial mon:stdio -nographic

clean:
	rm -f *.elf *.img
