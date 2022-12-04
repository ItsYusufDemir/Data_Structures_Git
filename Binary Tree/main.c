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
int findMin(TreeNodePtr root);
int findMax(TreeNodePtr root);
int find(TreeNodePtr root, int value);
void delete(TreeNodePtr *root, int value);
void printTree2D(TreeNodePtr tree);


int level = -1;

int main() {

    TreeNodePtr rootPtr = NULL;

    insertNode(&rootPtr, 45);
    insertNode(&rootPtr, 13);
    insertNode(&rootPtr, 24);
    insertNode(&rootPtr, 56);
    insertNode(&rootPtr, 78);
    insertNode(&rootPtr, 5);
    insertNode(&rootPtr, 8);
    insertNode(&rootPtr, 17);





    puts("The preorder traversal is:");
    preOrder(rootPtr);
    printf("\n\n");

    puts("The inorder traversal is:");
    inOrder(rootPtr);
    printf("\n\n");

    puts("The postorder traversal is:");
    postOrder(rootPtr);
    printf("\n\n");

    printf("Min number in the tree is: %d\n", findMin(rootPtr));
    printf("Max number in the tree is %d\n\n", findMax(rootPtr));

    delete(&rootPtr, 13);
    puts("After deleting 56:");
    inOrder(rootPtr);
    printf("\n\n");

    delete(&rootPtr, 5);
    puts("After deleting 5:");
    inOrder(rootPtr);
    printf("\n\n");

    delete(&rootPtr, 78);
    puts("After deleting 78:");
    inOrder(rootPtr);
    printf("\n\n");


    printTree2D(rootPtr);

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

int findMin(TreeNodePtr root){
    if(root == NULL){
        return NULL;
    }

    while(root->leftPtr != NULL){
        root = root->leftPtr;
    }
    return root->data;
}

int findMax(TreeNodePtr root){
    if(root == NULL){
        return NULL;
    }

    while(root->rightPtr != NULL){
        root = root->rightPtr;
    }
    return root->data;
}

int find(TreeNodePtr root, int value){
    if(root == NULL){
        return 0;
    }

    if(root->data == value){
        return 1;
    }
    else if(value > root->data)
        return  1 == find(root->rightPtr, value); //If it is found in the right subtree, that means if the find function return 1 then it will be equal to 1 (1==1) that will return 1.
    else
        return  1 == find(root->leftPtr, value);

}






void delete(TreeNodePtr *root, int value){

    if(root == NULL) //If the tree is empty return
        return;

    if((*root)->data == value){  //If the value is found

        if((*root)->rightPtr == NULL && (*root)->leftPtr == NULL){ //If the current root is a leaf
            TreeNodePtr temp = *root;
            *root = NULL;
            free(temp);
            return;
        }
        else if((*root)->rightPtr != NULL){  //If the right child exist
            (*root)->data = findMin((*root)->rightPtr); //Copy the min value of the right subtree to the node
            delete(&((*root)->rightPtr), findMin((*root)->rightPtr)); //Delete the duplicate value
            return;
        }
        else{ //If the left child exits
            (*root)->data = findMin((*root)->leftPtr);
            delete(&((*root)->leftPtr), findMin((*root)->leftPtr));
            return;
        }
    }
    else if (value > (*root)->data){
        delete(&((*root)->rightPtr), value);
        return;
    }
    else{
        delete(&((*root)->leftPtr), value);
        return;
    }

}


//Printing a tree in 2 dimensional
void printTree2D(TreeNodePtr tree) {//Recursive function --> RNL
    level++; //As we go deep, we increment the level

    if (tree != NULL) {
        printTree2D(tree->rightPtr);

        for(int i = 0; i < level; i++){ //Puts appropriate tabs
            printf("\t");
        }
        printf("%c\n", tree->data);


        printTree2D(tree->leftPtr);
    }

    level--;
}
//NOT WORKING !!!!

