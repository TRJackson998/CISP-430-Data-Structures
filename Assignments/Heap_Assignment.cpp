#include <fstream>
#include <iostream>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node* next;
    int index;
};

struct Queue {
    Node* front = NULL;
    Node* rear = NULL;
};

Node* newNode(int key) {
    Node* nnode = new Node;
    nnode->key = key;
    nnode->left = NULL;
    nnode->right = NULL;

    nnode->next = NULL;
    nnode->index = 0;
    return (nnode);
}

//enqueue (put @ rear)
void enqueue(Queue &Q, Node* new_node) {
    if(!Q.front) { //queue is empty, currently front = rear = NULL
        Q.front = Q.rear = new_node;
    }

    else { //queue is not empty
        Q.rear->next = new_node;
        Q.rear = new_node;
    }
}

//dequeue (take from front)
Node* dequeue(Queue &Q) {
    if(Q.front) {
        Node* val = newNode(0);
        Node* temp = Q.front;
        Q.front = Q.front->next;
        val = temp;
        if(!Q.front) {
            Q.rear = Q.front;
        }
        return val;
    }
    else {
        return NULL;
    }
}

int max(int array[], int arraySize) {
    int max = array[0];
    for(int i = 1; i < arraySize; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

int maxDigits(int max) {
    int digits = 0;
    while(max != 0) {
        digits++;
        max /= 10;
    }
    return digits;
}

void arrSort(int arr[], int arr_size) { //ascending radix sort
    Queue Buckets[10];
    int passes = maxDigits(max(arr, arr_size));
    int place = 1;
    Node* keyNode;
    for(int pass = 0; pass < passes; pass++) { //pass through ones place, tens place, etc
        int ibucket, iarray = 0;
        for(int i = 0; i < arr_size; i++) { //for each element of the array
            ibucket = arr[i] / place % 10;
            enqueue(Buckets[ibucket], newNode(arr[i]));
        }
        for(int i = 0; i < 10; i++) { //for each bucket
            while(Buckets[i].front) {
                keyNode = dequeue(Buckets[i]);
                arr[iarray] = keyNode->key;
                iarray++;
            }
        }
        place *= 10;
    }
}

void insertNode(Node* &curr, int arr[], int arr_size, int index) {
    if(!curr && (index < arr_size)) {
        curr = newNode(arr[index]);
        curr->index = index;
    }
    else {
        if(!curr->left && !curr->right) {
            if((2*index+1) < arr_size) {
                insertNode(curr->left, arr, arr_size, (2*index+1));
            }
            if((2*index+2) < arr_size) {
                insertNode(curr->right, arr, arr_size, (2*index+2));
            }
        }
        else if(curr->left && curr->right) {
            insertNode(curr->left, arr, arr_size, curr->left->index);
            insertNode(curr->right, arr, arr_size, curr->right->index);
        }
    }
}

void createHeap(Node* &root, int arr[], int arr_size) {
    root = newNode(arr[0]);
    for(int i = 0; i < arr_size; i++) {
        insertNode(root, arr, arr_size, i);
    }
}

void displayheap(Node* &curr, ostream &os) {
    Queue currLevel, nextLevel;
    enqueue(currLevel, curr); //enq root on current level
    while(currLevel.front) {
        os << currLevel.front->key << " ";
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
                curr = currLevel.front;
            }
            os << endl; //done, next line
        }
        else { //more nodes on this level, get the next one and continue enq children and printing
                curr = currLevel.front;
        }
    }
}

ifstream inf("input.txt");

int main() {
    //init variables
    int arr[10] = {0};
    int arr_size = 10;
    Node* root;

    //input values from file to array
    for(int i = 0; i < arr_size; i++) {
        inf >> arr[i];
    }

    //sort the array, create and display the heap
    arrSort(arr, arr_size);
    createHeap(root, arr, arr_size);
    cout << "Original min heap: \n";
    displayheap(root, cout);
    cout << endl;

    for(int i = 0; i < 5; i++) {
        //delete an item from the array
        for(int j = 0; j < arr_size-1; j++) {
            arr[j] = arr[j+1];
        }
        arr_size--;

        //recreate the heap
        root = NULL;
        createHeap(root, arr, arr_size);

        //display the heap
        cout << "Heap after delete " << i+1 << ": \n";
        displayheap(root, cout);
        cout << endl;
    }
    
    inf.close();
    return 0;
}

