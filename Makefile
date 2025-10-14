PORT ?= /dev/ttyUSB0
BIN_DIR = bin
SRC_DIR = src

SRCS := $(wildcard $(SRC_DIR)/*.c)
LIBS := $(SRC_DIR/*.h)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS))

CC := avr-gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99 -Os -mmcu=atmega328p

.PHONY: all

all: $(BIN_DIR) $(BIN_DIR)/main.hex

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) \
		-o $@ -c $<

$(BIN_DIR)/main.elf: $(OBJS)
	$(CC) $(CFLAGS) \
		-o $(BIN_DIR)/main.elf $(OBJS)

$(BIN_DIR)/main.hex: $(BIN_DIR)/main.elf
	avr-objcopy -O ihex -R .eeprom $(BIN_DIR)/main.elf $(BIN_DIR)/main.hex

upload: $(BIN_DIR)/main.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P $(PORT) -b 115200 -U flash:w:$(BIN_DIR)/main.hex

$(BIN_DIR):
	@if [ ! -d "$(BIN_DIR)" ]; then \
		mkdir -pv $(BIN_DIR);       \
	fi

size:
	avr-size --format=avr --mcu=atmega328p $(BIN_DIR)/main.elf

clean:
	rm -rf $(BIN_DIR)
