all: convert_loup_to_uplo.out uconvert_loup_to_uplo.out

convert_loup_to_uplo.out : convert_loup_to_uplo.o
	gcc convert_loup_to_uplo.o -o convert_loup_to_uplo.out

convert_loup_to_uplo.o : convert_loup_to_uplo.c
	gcc -c -MD convert_loup_to_uplo.c -o convert_loup_to_uplo.o

uconvert_loup_to_uplo.out : uconvert_loup_to_uplo.o
	gcc uconvert_loup_to_uplo.o -o uconvert_loup_to_uplo.out

uconvert_loup_to_uplo.o : convert_loup_to_uplo.c
	gcc -c -MD convert_loup_to_uplo.c -o uconvert_loup_to_uplo.o

-include $(OBJ_DIR)*.d

.PHONY : clean
clean:
	@rm convert_loup_to_uplo.d convert_loup_to_uplo.o convert_loup_to_uplo.out uconvert_loup_to_uplo.d uconvert_loup_to_uplo.o uconvert_loup_to_uplo.out 