all: threaded_server.out

threaded_server.out: threaded_server.o
	gcc $(CFLAGS) -pthread threaded_server.o -o threaded_server.out -lpthread

threaded_server.o : threaded_server.c
	gcc -c -MD $(CFLAGS) threaded_server.c -o threaded_server.o 

-include $(OBJ_DIR)*.d

.PHONY : clean
clean:
	@rm threaded_server.d threaded_server.o threaded_server.out