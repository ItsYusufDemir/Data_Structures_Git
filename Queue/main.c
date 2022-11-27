#include <stdio.h>
#include <stdlib.h>
/* Author: Yusuf Demir |||| GitHub-->@ItsYusufDemir
 * Starting date: 27.11.2022
 *
 * Project Description: Building a stack
 */

//STRUCTURES
struct queueNode{
    char data;
    struct queueNode *nextPtr;
};
typedef struct queueNode QueueNode;
typedef QueueNode *QueueNodePtr;

//FUNCTION PROTOTYPES
void printQueue(QueueNodePtr headPtr);
char dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr);
void enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, char value);
int isEmpty(QueueNodePtr head);




int main() {

    QueueNodePtr headPtr = NULL;
    QueueNodePtr tailPtr = NULL;

    enqueue(&headPtr, &tailPtr, 'B');
    enqueue(&headPtr, &tailPtr, 'F');
    enqueue(&headPtr, &tailPtr, 'A');
    enqueue(&headPtr, &tailPtr, 'Z');

    printQueue(headPtr);

    dequeue(&headPtr, &tailPtr);
    printQueue(headPtr);


    return 0;
}


void enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, char value){

    QueueNodePtr newQueue = malloc(sizeof(QueueNode));

    if(newQueue == NULL){
        printf("Memory is not available!");
        return;
    }

    newQueue->data = value;
    newQueue->nextPtr = NULL;

    if(isEmpty(*headPtr)){
        *headPtr = newQueue;
    }
    else{
        (*tailPtr)->nextPtr = newQueue;
    }
    *tailPtr = newQueue;

}

int isEmpty(QueueNodePtr head){
    return head == NULL;
}

char dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr){

    if(isEmpty(*headPtr)){
        printf("Queue is empty!\n");
        return '\0';
    }

    char value = (*headPtr)->data;
    QueueNodePtr temp = *headPtr;
    *headPtr = (*headPtr)->nextPtr;

    if(headPtr == NULL){
        *tailPtr = NULL;
    }

    free(temp);
    return value;
}


void printQueue(QueueNodePtr headPtr){

    printf("HEAD");
    while(headPtr != NULL){
        printf("---> %c ", headPtr->data);
        headPtr = headPtr->nextPtr;
    }
    printf("--->TAIL\n\n");
}
