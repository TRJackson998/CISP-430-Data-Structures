#include <iostream>
using namespace std;

//height is from ground up, depth is from top down

struct BinaryTree {
    int key;
    int height;
    BinaryTree* left;
    BinaryTree* right;
};

BinaryTree* newNode(int key) {
    BinaryTree* node = new BinaryTree;
    node-> key = key;
    node->left=NULL;
    node->right=NULL;
    return (node);
}

void insert(struct BinaryTree* &leaf, int item) {
    if (!leaf) {// Insertion place found.
        leaf = newNode(item);
    }
    else if (item < leaf->key) {
        insert(leaf->left, item) ;    //Insert in left subtree.
    }
    else if (item > leaf->key) {
        insert(leaf->right, item) ;   //Insert in right subtree.
    }    
}

int main() {
    struct BinaryTree* root = NULL;
    insert(root, 9);
    insert(root, 3);
    insert(root, 10);
    insert(root, 15);
    insert(root, 2);
}
