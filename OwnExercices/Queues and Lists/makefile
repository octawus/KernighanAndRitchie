all: initial_fooling_around.out list_exercice.out

initial_fooling_around.out : initial_fooling_around.o
	gcc initial_fooling_around.o -o initial_fooling_around.out

initial_fooling_around.o : initial_fooling_around.c
	gcc -c -MD initial_fooling_around.c -o initial_fooling_around.o

list_exercice.out : list_exercice.o
	gcc list_exercice.o -o list_exercice.out

list_exercice.o : list_exercice.c
	gcc -c -MD list_exercice.c -o list_exercice.o

-include $(OBJ_DIR)*.d

.PHONY : clean
clean:
	@rm list_exercice.d list_exercice.o list_exercice.out initial_fooling_around.d initial_fooling_around.o initial_fooling_around.out 