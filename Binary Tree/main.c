#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Author: Yusuf Demir  |   GitHub-->@ItsYusufDemir
 * Starting date: 229.11.2022
 *
 * Project Description: Building a binary tree
 */

//STRUCTRUES
struct treeNode{
    int data;
    struct treeNode *leftPtr;
    struct treeNode *rightPtr;
};
typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;

//FUNCTION PROTOTYPES
void postOrder(TreeNodePtr root);
void preOrder(TreeNodePtr root);
void inOrder(TreeNodePtr root);
void insertNode(TreeNodePtr *root, int value);



int main() {

    TreeNodePtr rootPtr = NULL;

    srand(time(NULL));

    //Add ten numbers between 0 and 100
    printf("Numbers: ");
    for(int i = 0; i < 7; i++){
        int randomm = rand() % 100;
        printf("%d ", randomm);
        insertNode(&rootPtr, randomm);
    }
    printf("\n\n");

    puts("The preorder traversal is:");
    preOrder(rootPtr);
    printf("\n\n");

    puts("The inorder traversal is:");
    inOrder(rootPtr);
    printf("\n\n");

    puts("The postorder traversal is:");
    postOrder(rootPtr);
    printf("\n\n");

    return 0;
}


void insertNode(TreeNodePtr *root, int value){

    //If the tree is empty
    if(*root == NULL){
        *root = malloc(sizeof(TreeNode));

        if(*root == NULL){
            printf("Memory is not available!\n");
            return;
        }
        else{
            (*root)->data = value;
            (*root)->leftPtr = NULL;
            (*root)->rightPtr = NULL;
        }
    }
    else{   //If the tree is not empty
        if(value == (*root)->data){ //Do nothing. We don't add same numbers again and again
            printf("The number %d is already in the tree!", value);
            return;
        }
        else if(value > (*root)->data){
            insertNode(&((*root)->rightPtr), value);
        }
        else{
            insertNode(&((*root)->leftPtr), value);
        }

    }

}

void inOrder(TreeNodePtr root){
    if(root != NULL) {
        inOrder(root->leftPtr);
        printf("%d ", root->data);
        inOrder(root->rightPtr);
    }
}

void preOrder(TreeNodePtr root){
    if(root != NULL) {
        printf("%d ", root->data);
        preOrder(root->leftPtr);
        preOrder(root->rightPtr);
    }
}

void postOrder(TreeNodePtr root){
    if(root != NULL) {
        postOrder(root->leftPtr);
        postOrder(root->rightPtr);
        printf("%d ", root->data);
    }
}


