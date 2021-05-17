all: input_sensibleness.out

input_sensibleness.out : input_sensibleness.o
	gcc input_sensibleness.o -o input_sensibleness.out

input_sensibleness.o : input_sensibleness.c
	gcc -c -MD input_sensibleness.c -o input_sensibleness.o

-include $(OBJ_DIR)*.d

.PHONY : clean
clean:
	@rm input_sensibleness.d input_sensibleness.o input_sensibleness.out 