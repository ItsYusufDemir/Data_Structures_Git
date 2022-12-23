#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Author: Yusuf Demir  |   GitHub-->@ItsYusufDemir
 * Starting date: 20.12.2022
 *
 * Project Description: Building an AVL tree
 */


//STRUCTURES
struct treeNode{
    int data;
    unsigned int height;
    struct treeNode *left;
    struct treeNode *right;
};
typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;


//GLOBAL VARIABLES
int height = -1;


//FUNCTION PROTOTYPES
void insertNode(TreeNodePtr *root, int value);
int findMax(TreeNodePtr root);
int findMin(TreeNodePtr root);
void inOrder(TreeNodePtr root);
void delete(TreeNodePtr *root, int value);
int max(int x, int y);
void rotateRR(TreeNodePtr *root);
void rotateLL(TreeNodePtr *root);
void copyTree(TreeNodePtr main, TreeNodePtr *duplicate);
void printTree2D(TreeNodePtr tree);




int main() {

    clock_t start, end;
    double cpu_time_used;
    start = clock();

















    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\n\n%f seconds\n",cpu_time_used);

    return 0;
}


void insertNode(TreeNodePtr *root, int value){

    if(*root == NULL) { //If the root is empty
        *root = malloc(sizeof(TreeNode));

        if(*root == NULL){ //Print an error if the memory is full and then return
            printf("Memory is not available! %d could not be inserted.");
            return;
        }

        (*root)->height = 0;
        (*root)->data = value;
        (*root)->right = NULL;
        (*root)->left = NULL;
    }
    else{

        if(value == (*root)->data)  //If the value is already in the tree, do nothing
            return;
        else if(value > (*root)->data)
            insertNode(&((*root)->right), value);
        else
            insertNode(&((*root)->left), value);

    }

}


int findMax(TreeNodePtr root){

    if(root == NULL)
        return NULL;

    while(root->right != NULL){  //Find the right-most child, which has the largest key
        root = root->right;
    }

    return root->data;
}


int findMin(TreeNodePtr root){

    if(root == NULL)
        return NULL;

    while(root->left != NULL){  //Find the left-most child, which has the smallest key
        root = root->left;
    }

    return root->data;
}


void delete(TreeNodePtr *root, int value){

    if(*root == NULL) //If the tree is empty, there is nothing to delete
        return;


    if((*root)->data == value) { //If the node that we will delete is found

        if((*root)->right == NULL && (*root)->left == NULL){//If the current root is a leaf which means has no children
            TreeNodePtr temp = *root;
            *root = NULL;
            free(temp);
        }
        else if((*root)->right != NULL){ //If the right child exist
            (*root)->data = findMin((*root)->right);   //Change the key with the smallest value in its right subtree
            delete(&((*root)->right), findMin((*root)->right)); //Delete the duplicate value
        }
        else{ //If it has only left child
            (*root)->data = findMax((*root)->left);
            delete(&((*root)->left), findMax((*root)->left));

        }

    }
    else if(value > (*root)->data){
        delete(&((*root)->right), value);
    }
    else{
        delete(&((*root)->left), value);
    }

}


void inOrder(TreeNodePtr root){
    if(root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}


void rotateRR(TreeNodePtr *root){
    TreeNodePtr temp;
    copyTree((*root), &temp);

    temp->right = (*root)->right->left;
    *root = (*root)->right;
    (*root)->left = temp;

};

void rotateLL(TreeNodePtr *root){
    TreeNodePtr temp;
    copyTree((*root), &temp);

    temp->left = (*root)->left->right;
    *root = (*root)->left;
    (*root)->right = temp;

};


void copyTree(TreeNodePtr main, TreeNodePtr *duplicate){  //Here we duplicate a tree so that same tree with different memory locations. We need this for rotations.

    if(main == NULL){  //We also copy the null variables
        *duplicate = NULL;
        return;
    }


    TreeNodePtr newTree = malloc(sizeof(TreeNode));
    newTree->data = main->data;
    newTree->height = main->height;
    copyTree(main->right, &(newTree->right)); //Recursive
    copyTree(main->left, &(newTree->left));

    *duplicate = newTree;
}


//Printing a tree in 2 dimensional
void printTree2D(TreeNodePtr tree) {//Recursive function --> RNL
    height++; //As we go deep, we increment the height

    if (tree != NULL) {
        printTree2D(tree->right);

        for(int i = 0; i < height; i++){ //Puts appropriate tabs
            printf("\t");
        }
        printf("%d\n", tree->data);


        printTree2D(tree->left);
    }

    height--;
}
