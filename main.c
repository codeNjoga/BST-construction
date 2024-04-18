#include <stdio.h>
#include <stdlib.h>

// Define the structure for the BST node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* bstconstruct(int inorder[], int postorder[], int start, int end, int* pIndex);
int search(int array[], int start, int end, int value);
Node* newNode(int data);
void printDFS(Node* node);

// Function to construct BST from in-order and post-order traversals
Node* bstconstruct(int inorder[], int postorder[], int start, int end, int* pIndex) {
    if (start > end) {
        return NULL;
    }

    // The last element in postorder is the root from the current segment
    Node* node = newNode(postorder[*pIndex]);
    (*pIndex)--;

    if (start == end) {
        return node;
    }

    // Find the index of this node in inorder traversal
    int iIndex = search(inorder, start, end, node->data);

    // Using index in Inorder traversal, construct right and then left subtree
    node->right = bstconstruct(inorder, postorder, iIndex + 1, end, pIndex);
    node->left = bstconstruct(inorder, postorder, start, iIndex - 1, pIndex);

    return node;
}

// Function to create a new node
Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to find the index of value in array[start...end]
int search(int array[], int start, int end, int value) {
    int i;
    for (i = start; i <= end; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1;
}

// Function to print nodes in DFS manner
void printDFS(Node* node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->data);
    printDFS(node->left);
    printDFS(node->right);
}

int main() {
    int inorder[] = {5, 10, 15, 20, 25, 30, 45};
    int postorder[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(inorder) / sizeof(inorder[0]);
    int postIndex = n - 1;

    Node* root = bstconstruct(inorder, postorder, 0, n - 1, &postIndex);

    printf("DFS of constructed BST: \n");
    printDFS(root);
    return 0;
}