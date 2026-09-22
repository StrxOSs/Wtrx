# ==== Toolchain ====
PREFIX := x86_64-linux-gnu-
CC     := $(PREFIX)gcc
LD     := $(PREFIX)ld
AS     := nasm
OBJCOPY:= $(PREFIX)objcopy

# ==== Directorios ====
LIBS      := libs
KERNEL    := kernel
DRIVERS   := drivers
ARCH      := arch
BUILD_DIR := bin

# ==== Flags ====
CFLAGS := -ffreestanding -fno-pic -fno-pie -mno-red-zone -mcmodel=kernel \
          -mno-mmx -mno-sse -mno-sse2 -Wall -Wextra -Werror -nostdlib -std=c11

INCLUDES := $(shell find $(LIBS) $(KERNEL) $(DRIVERS) $(ARCH) -name '*.h' | xargs -n1 dirname | sort -u | sed 's/^/-I/')

ASFLAGS := -f elf64

# ==== Fuentes ====
SOURCES_C   := $(shell find $(LIBS) $(KERNEL) $(DRIVERS) $(ARCH) -name '*.c')
SOURCES_ASM := $(shell find $(LIBS) $(KERNEL) $(DRIVERS) $(ARCH) -name '*.asm')

OBJECTS_C   := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCES_C))
OBJECTS_ASM := $(patsubst %.asm,$(BUILD_DIR)/%.o,$(SOURCES_ASM))
OBJECTS     := $(OBJECTS_C) $(OBJECTS_ASM)

# ==== Salida final ====
KERNEL_BIN := $(BUILD_DIR)/wtrx.bin
LINKER     := linker.ld

# ==== Reglas patrón ====
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "[CC] $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	@echo "[AS] $<"
	@$(AS) $(ASFLAGS) $< -o $@

# ==== Link final ====
$(KERNEL_BIN): $(OBJECTS) $(LINKER)
	@echo "[LD] $@"
	@$(LD) -T $(LINKER) -o $(KERNEL_BIN) $(OBJECTS)

# ==== IMG ====

KERNEL_IMG := $(BUILD_DIR)/wtrx.img

$(KERNEL_IMG): $(KERNEL_BIN)
	@cp $(KERNEL_BIN) $(KERNEL_IMG)
	@truncate -s 1474560 $(KERNEL_IMG)
	@echo "[IMG] $@"

# ==== Targets ====

all: $(KERNEL_BIN) $(KERNEL_IMG)
	@echo "[OK] the kernel is ready in $(KERNEL_BIN) and $(KERNEL_IMG)"

clean:
	@echo "[CLEAN] Borrando $(BUILD_DIR)"
	@rm -rf $(BUILD_DIR)

.PHONY: all clean
