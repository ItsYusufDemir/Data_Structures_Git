#include <stdio.h>
#include <stdlib.h>

/* Author: Yusuf Demir |||| GitHub-->@ItsYusufDemir
 * Starting date: 27.11.2022
 *
 * Project Description: Building a stack
 */


//STRUCTURES
struct stackNode{
    int data;
    struct stackNode *nextPtr;
};
typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;


//FUNCTION PROTOTYPES
int isEmpty(StackNodePtr stack);
int pop(StackNodePtr *topPtr);
int push(StackNodePtr *topPtr, int value);
void printStack(StackNodePtr stack);


int main() {

    StackNodePtr stackPtr = NULL;
    push(&stackPtr, 34);
    push(&stackPtr, 3234);
    push(&stackPtr, 314);
    push(&stackPtr, 75);

    printStack(stackPtr);

    pop(&stackPtr);
    pop(&stackPtr);

    printStack(stackPtr);

    return 0;
}

int push(StackNodePtr *topPtr, int value) {
    StackNodePtr newPtr = malloc(sizeof(StackNode));

    if (newPtr == NULL) {
        printf("Memory is not available!\n");
        return 0;
    }

    newPtr->data = value;
    newPtr->nextPtr = *topPtr;
    *topPtr = newPtr;
    return 1;
}


int pop(StackNodePtr *topPtr){

    if(isEmpty(*topPtr)){
        printf("Stack is empty!\n");
        return NULL;
    }

    int value = (*topPtr)->data;
    StackNodePtr temp = *topPtr;
    *topPtr = (*topPtr)->nextPtr;
    free(temp);
    return value;
}

int isEmpty(StackNodePtr stack){
    return stack == NULL;
}


void printStack(StackNodePtr stack){
    if(isEmpty(stack)){
        printf("Stack is empty!\n");
        return;
    }

    while(stack != NULL){
        printf("|    %-8d|\n", stack->data);
        stack = stack->nextPtr;
    }
    printf("--------------\n\n\n");
}


