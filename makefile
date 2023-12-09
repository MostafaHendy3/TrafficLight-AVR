# AVR Compiler and Programmer Configuration
AVRDUDE = avrdude
AVRDUDE_PROGRAMMER = your_programmer  # e.g., usbasp, usbtiny, etc.
AVRDUDE_PORT = /dev/ttyUSB0  # Specify your programmer's port
MCU = atmega32  # Replace with your AVR microcontroller model
F_CPU = 8000000UL  # Replace with your AVR's clock frequency

# Compiler and Linker Configuration
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
CFLAGS = -Wall -std=c99 -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

# Source files and output file
SRC_DIRS = MCAL HAL APP # Source directories
SRC_FILES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c)) $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*/*.c))
OUT_DIR = build
OUT_FILE = $(OUT_DIR)/output.hex
MAP_FILE = $(OUT_DIR)/output.map  # Memory map file

# Create the output directory if it doesn't exist
$(shell mkdir -p $(OUT_DIR))

# Define build targets
all: $(OUT_FILE)

$(OUT_FILE): $(SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $@ -Wl,-Map=$(MAP_FILE)
	$(OBJCOPY) -O ihex -R .eeprom $@ $(OUT_DIR)/output.hex

flash:
	$(AVRDUDE) -p $(MCU) -c $(AVRDUDE_PROGRAMMER) -P $(AVRDUDE_PORT) -U flash:w:$(OUT_FILE)

size:
	avr-size --format=avr --mcu=$(MCU) $(OUT_FILE)

clean:
	rm -rf $(OUT_DIR)

# Define phony targets
.PHONY: all flash size clean
