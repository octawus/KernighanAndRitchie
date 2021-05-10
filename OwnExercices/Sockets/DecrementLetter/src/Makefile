all: decrement_letter_server.out receiving_client.out sender_client.out

TARGET1 = $(BIN_DIR)/decrement_letter_server.out 
OBJ_DIR = ../obj
BIN_DIR = ../bin
SRC_DIR = .
UTILS_DIR = ./utils
INC_DIR = ../inc
CFLAGS  = -Wall -I $(INC_DIR)

decrement_letter_server.out: decrement_letter_server.o
	mkdir -p $(BIN_DIR)
	gcc $(CFLAGS) decrement_letter_server.o -o decrement_letter_server.out

receiving_client.out: receiving_client.o
	mkdir -p $(BIN_DIR)
	gcc $(CFLAGS) receiving_client.o -o receiving_client.out

sender_client.out: sender_client.o
	mkdir -p $(BIN_DIR)
	gcc $(CFLAGS) sender_client.o -o sender_client.out

decrement_letter_server.o : decrement_letter_server.c
	mkdir -p $(OBJ_DIR)
	gcc -c -MD $(CFLAGS) decrement_letter_server.c -o decrement_letter_server.o

receiving_client.o : receiving_client.c
	mkdir -p $(OBJ_DIR)
	gcc -c -MD $(CFLAGS) receiving_client.c -o receiving_client.o

sender_client.o : sender_client.c
	mkdir -p $(OBJ_DIR)
	gcc -c -MD $(CFLAGS) sender_client.c -o sender_client.o

-include $(OBJ_DIR)*.d

.PHONY : clean
clean:
	@rm -r $(OBJ_DIR) $(BIN_DIR)