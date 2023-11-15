#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node 
{
    int data;
    struct Node *left;
    struct Node *right;
    int height;
}
NODE;

int max(int a, int b) 
{
    return (a > b) ? a : b;
}

 
int height(NODE *high) 
{
    if (high == NULL)
        return 0;
    return high -> height;
}

int getBalance(NODE *bal) 
{
    if ( bal == NULL)
        return 0;
    return height(bal -> left) - height(bal -> right);
}

NODE *newNode(int val) 
{
    NODE *node = (NODE*)malloc(sizeof(NODE));
    node->data = val;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

NODE *rightRotate(NODE *r) {
    NODE *l = r -> left;
    NODE *T = l -> right;

    l -> right = r;
    r -> left = T;

    r -> height = max(height(r -> left), height(r -> right)) + 1;
    l -> height = max(height(l -> left), height(l -> right)) + 1;

    return l;
}

NODE *leftRotate(NODE *l) {
    NODE *r = l -> right;
    NODE *T = r -> left;

    r -> left = l;
    l -> right = T;

    l -> height = max(height(l -> left), height(l -> right)) + 1;
    r -> height = max(height(r -> left), height(r -> right)) + 1;

    return r;
}


NODE *insertUserAVL(NODE *node, int data) 
{
    if (node == NULL)
    {
        return newNode(data);
    }

    int direction;

    printf("Enter direction for key %d (1 for left, 2 for right, 0 for no rotation): ", data);
    scanf("%d", &direction);

    if (direction == 1)
    {
        node->left = insertUserAVL(node->left, data);
    }
    else if (direction == 2)
    {
        node->right = insertUserAVL(node->right, data);
    }
    else
        return node; 

    
    node -> height = 1 + max(height(node -> left), height(node -> right));
    int balance = getBalance(node);

   
    if (balance > 1 && data < node -> left -> data)
        return rightRotate(node);

    if (balance < -1 && data > node -> right -> data)
        return leftRotate(node);

    if (balance > 1 && data > node -> left -> data) {
        node -> left = leftRotate(node -> left);
        return rightRotate(node);
    }

    if (balance < -1 && data < node -> right -> data) {
        node -> right = rightRotate(node -> right);
        return leftRotate(node);
    }

    return node;
}

void inorderTraversal(struct Node *root) 
{
    if (root != NULL) 
    {
        inorderTraversal(root -> left);
        printf("%d ", root -> data);
        inorderTraversal(root -> right);
    }
}

bool compareAVLTrees(struct Node *root1, struct Node *root2) 
{
    if (root1 == NULL && root2 == NULL)
    {
        return true;
    }
    if (root1 == NULL || root2 == NULL)
    {
        return false;
    }

    return (root1->data == root2->data) && compareAVLTrees(root1->left, root2->left) && compareAVLTrees(root1->right, root2->right);
}


struct Node *insertToAVL(struct Node *node, int key) 
{
    if (node == NULL)
    {
        return newNode(key);
    }

    if (key < node->data)
    {
        node->left = insertToAVL(node->left, key);
    }
    else if (key > node->data)
    {
        node->right = insertToAVL(node->right, key);
    }
    else 
        return node;


    node->height = 1 + max(height(node -> left), height(node -> right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->data)
    {
        return rightRotate(node);
    }

    if (balance < -1 && key > node->right->data)
    {
        return leftRotate(node);
    }

    if (balance > 1 && key > node->left->data) 
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->data) 
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


int main() 
{
    struct Node *root_basic = NULL; 
    struct Node *root_user = NULL; 

    int elements[] = {3,2,4};
    int num_elements = sizeof(elements) / sizeof(elements[0]);

    
    for (int i = 0; i < num_elements; ++i)
    {
        root_basic = insertToAVL(root_basic, elements[i]);
    }


    for (int i = 0; i < num_elements; ++i)
    {
        root_user = insertUserAVL(root_user, elements[i]);
    }


    if (compareAVLTrees(root_basic, root_user))
        printf("Both trees are identical.\n");
    else
        printf("Trees differ.\n");

    return 0;
}
