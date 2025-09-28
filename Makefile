PORT ?= /dev/ttyUSB0
BIN_DIR = bin
SRC_DIR = src
INC_DIR = include

SRCS := $(wildcard $(SRC_DIR)/*.c)
LIBS := $(INC_DIR/*.h)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS))

CC := avr-gcc
CFLAGS := -Wall -Os -DF_CPU=16000000UL -mmcu=atmega328p -I ./$(INC_DIR)

.PHONY: all

all: $(BIN_DIR) compile

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) \
		-c $< -o $@
	@echo ""

compile: $(OBJS)
	$(CC) $(CFLAGS) \
		-o $(BIN_DIR)/main.elf $(OBJS)
	@echo ""
	avr-objcopy -O ihex -R .eeprom $(BIN_DIR)/main.elf $(BIN_DIR)/main.hex

upload: compile
	avrdude -F -V -c arduino -p ATMEGA328P \
		-P $(PORT) -b 115200 -U flash:w:$(BIN_DIR)/main.hex

$(BIN_DIR):
	@if [ ! -d "$(BIN_DIR)" ]; then          \
		echo "Creating folder '$(BIN_DIR)'"; \
		mkdir -p $(BIN_DIR);                 \
	fi

size:
	avr-size --format=avr --mcu=atmega328p $(BIN_DIR)/main.elf

clean:
	rm -rf $(BIN_DIR)
