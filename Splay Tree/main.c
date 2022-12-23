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
TreeNodePtr *findKey(TreeNodePtr *root, int key);
TreeNodePtr *findParent(TreeNodePtr *root, TreeNodePtr child);
void zigzigR(TreeNodePtr *X, TreeNodePtr *P, TreeNodePtr *G);
void zigzigL(TreeNodePtr *X, TreeNodePtr *P, TreeNodePtr *G);
void rotateRL(TreeNodePtr *root);
void rotateLR(TreeNodePtr *root);
void splay(TreeNodePtr *root, int inserted);




int main() {

    clock_t start, end;
    double cpu_time_used;
    start = clock();


    TreeNodePtr splayTree = NULL;

    /*
    insertNode(&splayTree, 6);
    insertNode(&splayTree, 5);
    insertNode(&splayTree, 3);
    insertNode(&splayTree, 2);
    insertNode(&splayTree, 10);
    insertNode(&splayTree, 30);
    insertNode(&splayTree, 48);
    insertNode(&splayTree, 12);
    insertNode(&splayTree, 11);
*/

    /*
    insertNode(&splayTree, 10);
    insertNode(&splayTree, 30);
    insertNode(&splayTree, 5);
    insertNode(&splayTree, 6);
    insertNode(&splayTree, 3);
    insertNode(&splayTree, 2);
    insertNode(&splayTree, 12);
    insertNode(&splayTree, 48);
    insertNode(&splayTree, 11);
    */


    insertNode(&splayTree, 50);
    insertNode(&splayTree, 30);
    insertNode(&splayTree, 60);
    insertNode(&splayTree, 10);
    insertNode(&splayTree, 40);
    insertNode(&splayTree, 90);
    insertNode(&splayTree, 70);
    insertNode(&splayTree, 100);
    insertNode(&splayTree, 20);
    insertNode(&splayTree, 15);






    printTree2D(splayTree);
    printf("\n\n");

    splay(&splayTree, 70);  //We will call the splay function after each insertion, but for now we will call it at the end with 11

    printTree2D(splayTree);









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


void splay(TreeNodePtr *root, int inserted) {

    if (*root == NULL)
        return;

    if ((*root)->data == inserted){
        return; //We are done.
    }
    else{ //Else, we will do some rotations

        if((*root)->left != NULL && (*root)->left->data == inserted){  //If the inserted key is currently is the left child of the root, we need a right rotation just same as in the AVL tree
            rotateLL(root);
        }
        else if((*root)->right != NULL && (*root)->right->data == inserted){  //If the inserted key is currently is the right child of the root, we need a left rotation just same as in the AVL tree
            rotateRR(root);
        }
        else {
            //Else find X,P, and G   (X is the inserted key, P is the parent of X and G is the grandparent of X
            //We need to clear that if the function enter here, that means P and G is exactly exits.


            TreeNodePtr *X = findKey(root, inserted);
            TreeNodePtr *P = findParent(root, *X);
            TreeNodePtr *G = findParent(root, *P);

            if ((*G)->left != NULL && (*G)->left->data == (*P)->data) {

                if ((*P)->left->data == (*X)->data) //Zig-zig left
                    zigzigL(X, P, G);

                else //RL Rotation
                    rotateRL(G);

            } else {

                if ((*P)->left != NULL && (*P)->left->data == (*X)->data) //LR Rotation
                    rotateLR(G);

                else //Zig-zig right
                    zigzigR(X, P, G);

            }
        }

    }

    splay(root, inserted); //We will do this procedure until the base case is executed
}


TreeNodePtr *findKey(TreeNodePtr *root, int key){  //This function finds the key and return its node recursively

    if((*root) == NULL) //The key is not found
        return NULL;

    if((*root)->data == key)
        return root;
    else if(key > (*root)->data){
        return findKey(&((*root)->right), key);
    }
    else
        return findKey(&((*root)->left), key);

}


TreeNodePtr *findParent(TreeNodePtr *root, TreeNodePtr child){

    if(root == NULL)
        return NULL; //That means child does not have a parent.

     if((*root)->right != NULL){
         if((*root)->right->data == child->data)
             return root;
     }

     if((*root)->left != NULL){
         if((*root)->left->data == child->data)
             return root;
     }

     if((*root)->data > child->data)
         return findParent(&((*root)->left), child);
     else
         return findParent(&((*root)->right), child);

}

void zigzigL(TreeNodePtr *X, TreeNodePtr *P, TreeNodePtr *G){ //Left zigzig

    TreeNodePtr tempG;
    copyTree(*G, &tempG);
    tempG->left = (*P)->right;

    TreeNodePtr tempP;
    copyTree(*P, &tempP);
    tempP->left = (*X)->right;
    tempP->right = tempG;

    *G = *X;
    (*G)->right = tempP;
}


void zigzigR(TreeNodePtr *X, TreeNodePtr *P, TreeNodePtr *G){ //Left zigzig

    TreeNodePtr tempG;
    copyTree(*G, &tempG);
    tempG->right = (*P)->left;

    TreeNodePtr tempP;
    copyTree(*P, &tempP);
    tempP->right = (*X)->left;
    tempP->left = tempG;

    *G = *X;
    (*G)->left = tempP;
}


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





