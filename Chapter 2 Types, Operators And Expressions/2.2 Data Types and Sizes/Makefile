all: determine_ranges.out 

determine_ranges.out: determine_ranges.o
	gcc $(CFLAGS) determine_ranges.o -o determine_ranges.out

determine_ranges.o: determine_ranges.c
	gcc -c -MD $(CFLAGS) determine_ranges.c -o determine_ranges.o


.PHONY : clean
clean:
	@rm determine_ranges.d determine_ranges.o determine_ranges.out 