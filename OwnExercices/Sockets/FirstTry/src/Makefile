TARGET1 = $(BIN_DIR)/tcp_client.out
TARGET2 = $(BIN_DIR)/tcp_server.out
OBJ_DIR = ../obj
BIN_DIR = ../bin
SRC_DIR = .
UTILS_DIR = ./utils
INC_DIR = ../inc
OBJS1  = $(OBJ_DIR)/tcp_client.o
OBJS2  = $(OBJ_DIR)/tcp_server.o
CFLAGS  = -Wall -I $(INC_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	gcc -c -MD $(CFLAGS) $< -o $@

$(TARGET2): $(OBJS2)
	mkdir -p $(BIN_DIR)
	gcc $(CFLAGS) $(OBJS2) -o $(TARGET2)

$(TARGET1): $(OBJS1)
	mkdir -p $(BIN_DIR)
	gcc $(CFLAGS) $(OBJS1) -o $(TARGET1)

-include $(OBJ_DIR)*.d

.PHONY : clean
clean:
	@rm -r $(OBJ_DIR) $(BIN_DIR)