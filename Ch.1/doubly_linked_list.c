#include <stdio.h>
#include <stdlib.h>



//defining Node
typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

int main() {
    //returning hello world
    printf("Hello World!\n");

    struct Node *head = NULL;

    int a = 5;
    int b = 10;
    int *c = &a;

    printf("%d\n", c);

    return 0;
}