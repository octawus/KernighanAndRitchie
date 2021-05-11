all: server.out cliente.out

server.out: server.o
	gcc $(CFLAGS) server.o -o server.out

server.o : server.c
	gcc -c -MD $(CFLAGS) server.c -o server.o

cliente.out: cliente.o
	gcc $(CFLAGS) cliente.o -o cliente.out

cliente.o : cliente.c
	gcc -c -MD $(CFLAGS) cliente.c -o cliente.o

-include $(OBJ_DIR)*.d

.PHONY : clean
clean:
	@rm server.d server.o server.out cliente.d cliente.o cliente.out
