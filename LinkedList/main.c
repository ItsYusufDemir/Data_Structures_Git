#include <stdio.h>
#include <stdlib.h>
/* Author: Yusuf Demir
 * Starting date: 27.11.2022
 *
 * Project Description: Building a linked list
 * sadf
 */


//STRUCTURES
struct listNode{
    char data;
    struct listNode *nextPtr;
};
typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;



//FUNCTION PROTOTYPES
void insert(ListNodePtr *sPtr, char value);
void printList(ListNodePtr currentPtr);
char delete(ListNodePtr *sPtr, char value);
int isEmpty(ListNodePtr sPtr);



int main() {

    ListNodePtr startPtr = NULL;

    insert(&startPtr, 'B');
    insert(&startPtr, 'C');
    insert(&startPtr, 'Z');
    insert(&startPtr, 'E');
    insert(&startPtr, 'A');

    printList(startPtr);
    printf("\n\n");

    delete(&startPtr, 'C');

    printList(startPtr);
    printf("\n\n");

    delete(&startPtr, 'B');

    printList(startPtr);
    printf("\n\n");

    return 0;
}


void insert(ListNodePtr *sPtr, char value){

    ListNodePtr newPtr = malloc(sizeof(ListNode));

    if(newPtr == NULL){
        printf("Memory is not available!");
        exit(0);
    }

    newPtr->data = value;
    newPtr->nextPtr = NULL;

    ListNodePtr previousPtr = NULL;
    ListNodePtr currentPtr = *sPtr;

    while(currentPtr != NULL && value > currentPtr->data){ //We will place our node between previous and current node.
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
    }

    if(previousPtr == NULL){  //If the node is empty or If the value should be placed in the beginning of the list
        newPtr->nextPtr = *sPtr;
        *sPtr = newPtr;
    }
    else {
        newPtr->nextPtr = currentPtr;
        previousPtr->nextPtr = newPtr;
    }

}


char delete(ListNodePtr *sPtr, char value){

    if(isEmpty(*sPtr)){
        printf("Linked List is empty!\n");
        return '\n';
    }

    if((*sPtr)->data == value){
        ListNodePtr temp = *sPtr;
        *sPtr = (*sPtr)->nextPtr;
        free(temp);
        return value;
    }
    else{

        ListNodePtr currentPtr = *sPtr;
        ListNodePtr previousPtr = NULL;

        while(currentPtr != NULL && value != currentPtr->data){
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }


        if(currentPtr == NULL){
            printf("%c is not in the list!\n");
            return '\0';
        }
        else{
            ListNodePtr temp = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free(temp);
            return value;
        }

    }


}

int isEmpty(ListNodePtr sPtr){
    return sPtr == NULL;
}


void printList(ListNodePtr currentPtr){

    if(isEmpty(currentPtr)){
        printf("List is empty!\n");
    }

    while(currentPtr != NULL){
        printf("%c--->", currentPtr->data);
        currentPtr = currentPtr->nextPtr;
    }

    printf("NULL\n");

}
