#include <fstream>
using namespace std;

struct node {
    int key;
    int height = -1;
    node* left;
    node* right;
};

int max(int left, int right) {
    if(left >= right) {
        return left;
    }
    else {
        return right;
    }
}

int height(node* node) {
    if(node) {
        return node->height;
    }
    else {
        return -1;
    }
}

int getBalance(node* node) {
    int lHeight = -1, rHeight = -1;
    if(node->left) {
        lHeight = height(node->left);
    }
    if(node->right) {
        rHeight = height(node->right);
    }
    return lHeight - rHeight;
}

node* newNode(int key) {
    node* nnode = new node;
    nnode-> key = key;
    nnode->left = NULL;
    nnode->right = NULL;
    nnode->height = 0;
    return (nnode);
}

node* leftRotate(node* x){   
    struct node* y = x->right;
    node* z = y->left;
    y->left = x;
    x->right = z;
    
    //node->height = max(height(node->left), height(node->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

node* rightRotate(node* x){   
    node* y = x->left;
    node* z = y->right;
    x->left = z;
    y->right = x;
    
    //node->height = max(height(node->left), height(node->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

//I will not accept any other algorithm
//This is not a recursive algorithm
node * rebalance(node *node){
    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);  //node->left - node->right
    int child_balance;

    //rotations as necessary
    if(balance == 2) {
        child_balance = getBalance(node->left);
        if(child_balance == 1) {
            //left heavy ouside
            return rightRotate(node);
        }
        else if(child_balance == -1) {
            //left heavy inside
            node->left =  leftRotate(node->left);
            return rightRotate(node); 
        }
        else {
            return node;
        }
    }
    else if(balance == -2) {
        child_balance = getBalance(node->right);
        if(child_balance == -1) {
            //right heavy outside
            return leftRotate(node);
        }
        else if(child_balance == 1) {
            //right heavy inside
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        else {
            return node;
        }
    }
    else {
        //no rotation
        return node;
    }
}


//non-tail recursive algorithm because of rebalance 
node* insert(node* node, int key) {    
    //recursive Code for inserting a node     
    //When insert happens set height to 0 for the node         
    if (node == NULL) {
        return(newNode(key));
    }

    if (key < node->key) {
        node->left  = insert(node->left, key);    
    }
    else {
        node->right = insert(node->right, key);    
    }

    node = rebalance(node);  //update heights and rebalance    
    return node;
}

//Queue FIFO
struct QNode {
    node* tree;
    QNode* next = NULL;
};

struct Queue {
    QNode* front = NULL;
    QNode* rear = NULL;
};

//enqueue (put @ rear)
void enqueue(Queue &Q, node* tree) {
    QNode* nn = new QNode;
    nn->tree = tree;
    nn->next = NULL;

    if(!Q.front) { //queue is empty, currently front = rear = NULL
        Q.front = Q.rear = nn;
    }

    else { //queue is not empty
        Q.rear->next = nn;
        Q.rear = nn;
    }
}

//dequeue (take from front)
node* dequeue(Queue &Q) {
    if(Q.front) {
        node* val;
        QNode* temp = Q.front;
        Q.front = Q.front->next;
        val = temp->tree;
        delete temp;
        if(!Q.front) {
            Q.rear = Q.front;
        }
        return val;
    }
    else {
        return NULL;
    }
}

void displayTree(node* &curr, ostream &os) {
    Queue currLevel, nextLevel;
    enqueue(currLevel, curr); //enq root on current level
    while(currLevel.front) {
        os << currLevel.front->tree->key 
           << " (" << height(currLevel.front->tree)
           << "," << getBalance(currLevel.front->tree) << ") "; //display current level
        if(curr->left) { //enq left child, if there
            enqueue(nextLevel, curr->left);
        }
        if(curr->right) { //enq right child, if there
            enqueue(nextLevel, curr->right);
        }        
        dequeue(currLevel); //deq current node

        if(currLevel.front == NULL) { //no more nodes on this level
            //swap to work with the next level as the new current level
            currLevel.front = nextLevel.front;
            currLevel.rear = nextLevel.rear;
            nextLevel.front = nextLevel.rear = NULL;
            if(currLevel.front) { //if there are nodes to work with on the NEW current level, reset curr
                curr = currLevel.front->tree;
            }
            os << endl; //done, next line
        }
        else { //more nodes on this level, get the next one and continue enq children and printing
                curr = currLevel.front->tree;
        }
    }
}

int main() {
    ifstream inf("input.txt");
    ofstream outf("output.txt");

    node* rootAVL = NULL;
    int key;

    inf >> key;
    while(!inf.eof()) {
        //put the key in the AVL
        rootAVL = insert(rootAVL, key);
        //get the next key
        inf >> key;
    }
    rootAVL = insert(rootAVL, key);

    outf << "AVL Tree printed in levels\nNode (height, balance factor)\n";
    //print the tree at the end
    displayTree(rootAVL, outf);


    //
}