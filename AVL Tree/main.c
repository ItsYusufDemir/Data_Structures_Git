#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* Author: Yusuf Demir  |   GitHub-->@ItsYusufDemir
 * Starting date: 29.11.2022
 *
 * Project Description: Building a binary tree
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



//FUNCTION PROTOTYPES
void insertNode(TreeNodePtr *root, int value);
int findMax(TreeNodePtr root);
int findMin(TreeNodePtr root);
void inOrder(TreeNodePtr root);
void delete(TreeNodePtr *root, int value);
int max(int x, int y);
int findHeight(TreeNodePtr root);
void updateHeights(TreeNodePtr *root);
void checkBalance(TreeNodePtr *root);
void balanceAVL(TreeNodePtr *root);





int main() {

    clock_t start, end;
    double cpu_time_used;
    start = clock();



    TreeNodePtr rootPtr = NULL;

    insertNode(&rootPtr, 45);
    //checkBalance(&rootPtr); // After inserting a value, we should balance it
    insertNode(&rootPtr, 13);
    insertNode(&rootPtr, 24);
    insertNode(&rootPtr, 56);
    insertNode(&rootPtr, 78);
    insertNode(&rootPtr, 5);
    insertNode(&rootPtr, 8);
    insertNode(&rootPtr, 17);
    insertNode(&rootPtr, 9);

    checkBalance(&rootPtr);





    puts("The inorder traversal is:");
    inOrder(rootPtr);
    printf("\n\n");





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

    updateHeights(root); //After we insert a node, we update all the heights of the nodes in the tree
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


void updateHeights(TreeNodePtr *root){ //We update all the height of a tree recursively

    if(*root == NULL)
        return;

    updateHeights(&((*root)->left));
    updateHeights(&((*root)->right));
    (*root)->height = findHeight(*root);
}

int findHeight(TreeNodePtr root){  //Finding the height of a node recursively

    if(root == NULL)
        return -1; //Return 0 for leaves

    //Height of a node is: max height of right and left subtree + 1
    unsigned int rightHeight = findHeight(root->right);
    unsigned int leftHeight = findHeight(root->left);

    return max(leftHeight, rightHeight) + 1;
}

int max(int x, int y){ //A simple finding the max is needed
    if(x > y)
        return x;
    else
        return y;
}


void checkBalance(TreeNodePtr *root){ //We check each node in the tree recursively and correct if there is a violation of AVL rule

    if(*root == NULL)
        return;

    checkBalance(&((*root)->left));
    checkBalance(&((*root)->right));

    if((*root)->right == NULL && (*root)->left == NULL) //If the current root is a leaf, there is nothing to check
        return;
    else if((*root)->right == NULL) {  //If the root has only left child

        if( abs((*root)->left->height - (-1)) > 1)
            balanceAVL(root);
    }
    else{ //If the root has only right child

        if(abs((*root)->right->height - (-1)) > 1)
            balanceAVL(root);
    }

}



void balanceAVL(TreeNodePtr *root){




}




