all: threaded_server_able_write.out threaded_server.out client.out 

threaded_server.out: threaded_server.o
	gcc $(CFLAGS) -pthread threaded_server.o -o threaded_server.out -lpthread

threaded_server.o : threaded_server.c
	gcc -c -MD $(CFLAGS) threaded_server.c -o threaded_server.o 

client.out: client.o
	gcc $(CFLAGS) -pthread client.o -o client.out -lpthread

client.o : client.c
	gcc -c -MD $(CFLAGS) client.c -o client.o 

threaded_server_able_write.out: threaded_server_able_write.o
	gcc $(CFLAGS) -pthread threaded_server_able_write.o -o threaded_server_able_write.out -lpthread

threaded_server_able_write.o : threaded_server_able_write.c
	gcc -c -MD $(CFLAGS) threaded_server_able_write.c -o threaded_server_able_write.o 

-include $(OBJ_DIR)*.d

.PHONY : clean
clean:
	@rm threaded_server.d threaded_server.o threaded_server.out client.d client.o client.out threaded_server_able_write.d threaded_server_able_write.o threaded_server_able_write.out