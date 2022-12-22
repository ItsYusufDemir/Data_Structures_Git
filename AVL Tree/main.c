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


int height = -1;


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
int getHeight(TreeNodePtr root);
void rotateRR(TreeNodePtr *root);
void rotateLL(TreeNodePtr *root);
void rotateRL(TreeNodePtr *root);
void rotateLR(TreeNodePtr *root);
void copyTree(TreeNodePtr main, TreeNodePtr *duplicate);
void printTree2D(TreeNodePtr tree);







int main() {

    clock_t start, end;
    double cpu_time_used;
    start = clock();



    TreeNodePtr rootPtr = NULL;

    /*
    insertNode(&rootPtr, 21);
    insertNode(&rootPtr, 26);
    insertNode(&rootPtr, 30);
    insertNode(&rootPtr, 9);
    insertNode(&rootPtr, 4);
    insertNode(&rootPtr, 14);
    insertNode(&rootPtr, 28);
    insertNode(&rootPtr, 18);
    insertNode(&rootPtr, 15);
    insertNode(&rootPtr, 10);
    insertNode(&rootPtr, 2);
    insertNode(&rootPtr, 3);
    insertNode(&rootPtr, 7);
    */

    /*
    insertNode(&rootPtr, 14);
    insertNode(&rootPtr, 17);
    insertNode(&rootPtr, 11);
    insertNode(&rootPtr, 7);
    insertNode(&rootPtr, 53);
    insertNode(&rootPtr, 4);
    insertNode(&rootPtr, 13);
    insertNode(&rootPtr, 12);
    insertNode(&rootPtr, 8);
    insertNode(&rootPtr, 60);
    insertNode(&rootPtr, 19);
    insertNode(&rootPtr, 16);
    insertNode(&rootPtr, 20);
*/

    insertNode(&rootPtr, 9);
    insertNode(&rootPtr, 15);
    insertNode(&rootPtr, 20);
    insertNode(&rootPtr, 8);
    insertNode(&rootPtr, 7);
    insertNode(&rootPtr, 13);
    insertNode(&rootPtr, 10);




    printTree2D(rootPtr);
    printf("\n\n");


    //checkBalance(&rootPtr);











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
    checkBalance(root);
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

    if(abs(getHeight((*root)->right) - getHeight((*root)->left)) > 1)
        balanceAVL(root);

}



void balanceAVL(TreeNodePtr *root){

    //Here we get the problematic subtree with its root
    //First we will find the which type of rotation we need: LL, RR, LR, RL
    //Then we will call the right rotation function


    if(getHeight((*root)->right) > getHeight((*root)->left)){ //Our Rotation is RR or LR

        if(getHeight((*root)->right->right) > getHeight((*root)->right->left))
            rotateRR(root);
        else
            rotateLR(root);
    }
    else{ //Our Rotation is LL or RL

        if(getHeight((*root)->left->left) > getHeight((*root)->left->right))
            rotateLL(root);
        else
            rotateRL(root);
    }


    updateHeights(root); //After a rotation, we update the height of the tree

}


int getHeight(TreeNodePtr root){  //To get the NULL nodes height, we use this simple function
    if (root != NULL)
        return root->height;
    else
        return -1;
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



void rotateRL(TreeNodePtr *root){
    int key = (*root)->left->right->data;
    TreeNodePtr temp;
    copyTree((*root), &temp);

    temp->left = (*root)->left->right->right;
    (*root)->left->right = (*root)->left->right->left;
    (*root)->data = key;
    (*root)->right = temp;

};






void rotateLR(TreeNodePtr *root){
    int key = (*root)->right->left->data;
    TreeNodePtr temp;
    copyTree((*root), &temp);

    temp->right = (*root)->right->left->left;
    (*root)->right->left = (*root)->right->left->right;
    (*root)->data = key;
    (*root)->left = temp;

};





void copyTree(TreeNodePtr main, TreeNodePtr *duplicate){  //Here we duplicate a tree so that same tree with different memory locations. We need this for rotations.

    if(main == NULL){
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




