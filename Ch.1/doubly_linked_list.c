#include <stdio.h>
#include <stdlib.h>

//defining Node
typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

//making head and tail a global variable
struct Node *head = NULL;
struct Node *tail = NULL;

//function for creating a new node for insertAtHead function
struct Node *getNewNode(int x) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("malloc");
        exit(1);
    }
    newNode->data = x;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

//inserting node at the head of the list
void insertAtHead(int x) {
    struct Node *newNode = getNewNode(x);
    if (head == NULL) {
        head = tail = newNode;
        return;
    }
    head->prev = newNode;
    newNode->next = head;
    head = newNode;
    return;

}

void insertAtTail(int x) {
    struct Node *newNode = getNewNode(x);
    if (head == NULL) {
        head = tail = newNode;
    }

    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
    return;
}

//function to find a node
void findNode(int x) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    while (temp != NULL) {
        if (temp->data == x) {
            printf("%d exists\n", x);
            return;
        }
        temp = temp->next;
    }
    printf("%d does not exist\n", x);
    return;
}

//printing function to return the list
void Print() {
    struct Node *temp = head;
    printf("Forward: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

}


//testing functions
int main() {

    insertAtHead(10);
    insertAtHead(20);
    insertAtTail(100);

    findNode(9);

    Print();

    return 0;
}