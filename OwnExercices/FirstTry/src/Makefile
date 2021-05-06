TARGET  = $(BIN_DIR)/arrays_and_pointers_fooling_around.out
OBJ_DIR = ../obj
BIN_DIR = ../bin
SRC_DIR = .
UTILS_DIR = ./utils
INC_DIR = ../inc
OBJS    = $(OBJ_DIR)/string_processing.o\
	      $(OBJ_DIR)/arrays_and_pointers_fooling_around.o
CFLAGS  = -Wall -I $(INC_DIR)


$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	gcc $(CFLAGS) $(OBJS) -o $(TARGET)

#string_processing.o: string_processing.c ../Headers/string_processing.h
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	gcc -c -MD $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o : $(UTILS_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	gcc -c -MD $(CFLAGS) $< -o $@

-include $(OBJ_DIR)*.d

.PHONY : clean
clean:
	@rm -r $(OBJ_DIR) $(BIN_DIR)