#include <stdio.h>
#include <stdlib.h>
#include <linux/list.h> //https://www.cs.uic.edu/~hnagaraj/articles/linked-list/
#include <string.h>
#include <assert.h>

struct Node {
    char name[30];
    int age;
    struct list_head list_member;
};

void add_node(char *nameArg, int ageArg, struct list_head *head){
    struct Node *nodePtr = (struct Node *)malloc(sizeof(struct Node));
    assert(nodePtr != NULL);

    strcpy(nodePtr -> name, nameArg);
    nodePtr -> age = ageArg;
    INIT_LIST_HEAD(&nodePtr -> list_member);
    list_add(&nodePtr -> list_member, head);
}

void display(struct list_head *head)
{
    struct list_head *iter;
    struct Node *objPtr;

    __list_for_each(iter, head){
        objPtr = list_entry(iter, struct Node, list_member);
        printf("%s: %d\n", objPtr -> name, objPtr -> age);
    }
    
};

void delete_all(struct list_head *head){
    struct list_head *iter;
    struct Node *objPtr;
    
redo:
    __list_for_each(iter, head){
        objPtr = list_entry(iter, struct Node, list_member);
        list_del(&objPtr -> list_member);
        free(objPtr);
        goto redo;
    }
}


int find_first_and_delete(char * argName, struct list_head *head)
{
    struct list_head *iter;
    struct Node *objPtr;

    __list_for_each(iter, head) {
        objPtr = list_entry(iter, struct Node, list_member);
        if(strcmp(objPtr -> name, argName) == 0) {
            list_del(&objPtr->list_member);
            free(objPtr);
            return 1;
        }
    }

    return 0;
}

int main()
{
    LIST_HEAD(hnode);

    add_node("Mihai", 23, &hnode);
    add_node("Sara", 25, &hnode);
    add_node("Javier", 22, &hnode);

    display(&hnode);

    printf("\n");

    find_first_and_delete("Mihai", &hnode);

    add_node("abc", 123, &hnode);
    display(&hnode);

    delete_all(&hnode);

    return 0;
}