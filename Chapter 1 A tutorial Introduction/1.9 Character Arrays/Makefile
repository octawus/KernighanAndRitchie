all: reverse_characters.out 

reverse_characters.out: reverse_characters.o
	gcc $(CFLAGS) reverse_characters.o -o reverse_characters.out

reverse_characters.o: reverse_characters.c
	gcc -c -MD $(CFLAGS) reverse_characters.c -o reverse_characters.o


.PHONY : clean
clean:
	@rm reverse_characters.d reverse_characters.o reverse_characters.out 