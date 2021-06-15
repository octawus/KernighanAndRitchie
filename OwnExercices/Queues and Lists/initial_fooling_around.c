#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct _Cat {
        //struct _Cat *next;
        LIST_ENTRY(_Cat) pointers;

        /*struct {								
	        struct _Cat *le_next;	// next element			
	        struct _Cat **le_prev;	// address of previous next element	
        } pointers
        
        This macro creates the pointer structure for the forward and
        backward linkage.

        So for example you can do Cat.pointers.le_next
        or Cat.pointers.le_prev ("le" might mean "list element")

        Basically, LIST_ENTRY lets you generate the part of code that
        actually makes a structure a node in a list.
        */

        char name[255];
        int color;
        char can_climb;
} Cat;

typedef struct _Dog {
        //struct _Dog *next;
        LIST_ENTRY(_Dog) pointers;

        /*struct {								
	        struct _Dog *le_next;	// next element			
	        struct _Dog **le_prev;	// address of previous next element	
        } pointers
        
        Same as before but for dog.

        */

        char name[255];
        int color;
        char can_swim;
} Dog;

/*Declare functions (later defined), to create new cats and dogs*/
Cat *create_cat(char *name, int color, char can_climb);
Dog *create_dog(char *name, int color, char can_swim);

LIST_HEAD(cat_list, _Cat) cats;
/*
struct cat_list {								
	struct _Cat *lh_first;	//first element			
}cats

Creates the actual list. The inner struct holds the pointer to the
first element.l
*/ 

LIST_HEAD(dog_list, _Dog) dogs;
/*
struct dog_list {								
	struct _Dog *lh_first;	//first element			
}dogs
*/ 

int main()
{
        printf("\n--------------EXAMPLE------------------\n");
        /*4 cat structs are created. See creation method explanation
        down below.*/
        Cat *cat1 = create_cat("Cat1", 2, 0);
        Cat *cat2 = create_cat("Cat2", 3, 1);
        Cat *cat3 = create_cat("Cat3", 4, 0);
        Cat *cat4 = create_cat("Cat4", 2, 0);

        /*The pointers inside the structs dont actually know 
        where to point until now*/
        /*Point the first element to NULL*/
        LIST_INIT(&cats);
        LIST_INSERT_HEAD(&cats, cat1, pointers);
        /*
        #define	LIST_INSERT_HEAD(&cats, cat1, pointers) do {	

	        if (((cat1)->pointers.le_next = (&cats)->lh_first) != NULL)	

		        (&cats)->lh_first->pointers.le_prev = &(cat1)->pointers.le_next;
	        
            (&cats)->lh_first = (cat1);					
	        
            (cat1)->pointers.le_prev = &(&cats)->lh_first;	

        } while (/*CONSTCOND0) //Comment CONSTCOND0!!!
        */

        LIST_INSERT_HEAD(&cats, cat2, pointers);
        LIST_INSERT_AFTER(cat2, cat3, pointers);
        LIST_INSERT_AFTER(cat3, cat4, pointers);
        LIST_REMOVE(cat4, pointers);
        Cat *cat;
        LIST_FOREACH(cat, &cats, pointers) {
                printf("\n%s", cat->name);
        }
        printf("\n");
        Dog *dog1 = create_dog("Dog1", 2, 0);
        Dog *dog2 = create_dog("Dog2", 3, 1);
        Dog *dog3 = create_dog("Dog3", 4, 0);
        Dog *dog4 = create_dog("Dog4", 2, 0);
        LIST_INIT(&dogs);
        LIST_INSERT_HEAD(&dogs, dog1, pointers);
        LIST_INSERT_HEAD(&dogs, dog2, pointers);
        LIST_INSERT_AFTER(dog2, dog3, pointers);
        LIST_INSERT_AFTER(dog3, dog4, pointers);
        LIST_REMOVE(dog4, pointers);
        Dog *dog;
        LIST_FOREACH(dog, &dogs, pointers) {
                printf("\n%s", dog->name);
        }
        printf("\n");
}

/*The following explanation stands true for both creation methods.
Accept as parameters a name, a color and a can_climb characteristics.

The create a pointer to a Cat (so that the cat is accessible from
outside the function) and assign memory if size Cat struct.

Then copy the name accepted as a parameter to the name inside
the new struct.

Same for other parameters.

3 invocations of this method should result in a memory 
state like the following. (suppose sizeof(Cat/Dog) is 300 bytes
and sizeof(*cat) is 8 bytes -for 64 bits systems-)

---------------------------BEGINNING OF MEMORY----------------------
...................................................................
...................................................................
0x1000 -> pointer to Cat struct (*cat1 -> 0x5000)
0x1010 -> pointer to Cat struct (*cat2 -> 0x7432)
0x1018 -> pointer to Cat struct (*cat3 -> 0xAA99)
...................................................................
...................................................................
0x5000 -> Cat struct initial position.
...................................................................
...................................................................
...................................................................
0x7432 -> Cat struct initial position.
...................................................................
...................................................................
...................................................................
0xAA99 -> Cat struct initial position.
...................................................................
...................................................................
...................................................................
---------------------------END OF MEMORY---------------------------

*/
Cat *create_cat(char *name, int color, char can_climb) {
        Cat *cat = (Cat *)malloc(sizeof(Cat));
        strcpy(cat->name, name);
        cat->color = color;
        cat->can_climb = can_climb;
}
Dog *create_dog(char *name, int color, char can_swim) {
        Dog *dog = (Dog *)malloc(sizeof(Dog));
        strcpy(dog->name, name);
        dog->color = color;
        dog->can_swim = can_swim;
}