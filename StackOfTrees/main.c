#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Author: Yusuf Demir  |   GitHub-->@ItsYusufDemir
 * Starting date: 229.11.2022
 *
 * Project Description: Building a binary tree from a arithmetic expression.
 */

//STRUCTURES
struct treeNode{
    char data;
    struct treeNode *rightPtr;
    struct treeNode *leftPtr;
};
typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;

struct stackNode{
    TreeNodePtr tree;
    struct stackNode *nextPtr;
};
typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;





//FUNCTION PROTOTYPES
int push(StackNodePtr *head, TreeNodePtr tree);
TreeNodePtr pop(StackNodePtr *head);
TreeNodePtr createTree(char value, TreeNodePtr right, TreeNodePtr left);
int isOperand(char value);

int main(void){

    StackNodePtr head = NULL;

    FILE *fptr = fopen("", "r");
    if(fptr == NULL){
        printf("File could not opened! Check the path!\n");
        exit(42);
    }


    int currentItem;
    while((currentItem = fgetc(fptr)) != NULL){

        if(currentItem == ' ' || currentItem == '\n')//Ignore blanks and new line chars
            continue;

        TreeNodePtr newTree = createTree(currentItem, NULL, NULL);

        if(isOperand(currentItem)){ //If the token is an operator
            TreeNodePtr left = pop(&head);
            TreeNodePtr right = pop(&head);

            push(&head, createTree(newTree, right, left));

        }
        else{ //If the token is an operand
            push(&head, newTree);
        }
    }








    return 0;
}

int push(StackNodePtr *head, TreeNodePtr tree){
    StackNodePtr newPtr = malloc(sizeof(StackNode));

    if(newPtr == NULL){
        printf("Memory is not available!\n");
        return 0; //Fail
    }

    newPtr->tree = tree;
    newPtr->nextPtr = *head;
    *head = newPtr;
    return 1;
}

TreeNodePtr pop(StackNodePtr *head){
    StackNodePtr temp = *head;
    *head = (*head)->nextPtr;
    return temp;
}

TreeNodePtr createTree(char value, TreeNodePtr right, TreeNodePtr left){ //Create a new tree from a two subtree
    TreeNodePtr newPtr = malloc(sizeof(TreeNode));
    if(newPtr == NULL){
        printf("Memory is not available!\n");
    }

    newPtr->data = value;
    newPtr->rightPtr = right;
    newPtr->leftPtr = left;

    return newPtr;
}


int isOperand(char value){
    if(value == '+' || value == '-' || value == '*' || value == '/')
        return 1;
    else
        return 0;
}