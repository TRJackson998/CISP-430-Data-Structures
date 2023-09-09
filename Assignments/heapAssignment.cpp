#include <fstream>
#include <iostream>

using namespace std;

struct node {
    int key;
    node* left;
    node* right;
};

struct QNode {
    node* heap;
    QNode* next = NULL;
};

struct Queue {
    QNode* front = NULL;
    QNode* rear = NULL;
};

node* newNode(int key) {
    node* nnode = new node;
    nnode-> key = key;
    nnode->left = NULL;
    nnode->right = NULL;
    return (nnode);
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

void enqueue(Queue &Q, int value) {
    node* nn = newNode(value);

    if(!Q.front) { //queue is empty, currently front = rear = NULL
        Q.front = Q.rear = nn;
    }

    else { //queue is not empty
        Q.rear->next = nn;
        Q.rear = nn;
    }
}

void ascendingRadix(int arr[], int arr_size) {
    Queue Buckets[10];
    int passes = maxDigits(max(arr, arr_size));
    int place = 1;
    for(int pass = 0; pass < passes; pass++) { //pass through ones place, tens place, etc
        int ibucket, iarray = 0;
        for(int i = 0; i < arr_size; i++) { //for each element of the array
            ibucket = arr[i] / place % 10;
            enqueue(Buckets[ibucket], arr[i]);
        }
        for(int i = 0; i < 10; i++) { //for each bucket
            while(Buckets[i].front) {
                arr[iarray] = dequeue(Buckets[i]);
                iarray++;
            }
        }
        place *= 10;
    }
}

//enqueue (put @ rear)
void enqueue(Queue &Q, node* heap) {
    QNode* nn = new QNode;
    nn->heap = heap;
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
        val = temp->heap;
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

void displayheap(node* &curr, ostream &os) {
    Queue currLevel, nextLevel;
    enqueue(currLevel, curr); //enq root on current level
    while(currLevel.front) {
        os << currLevel.front->heap->key << " ";
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
                curr = currLevel.front->heap;
            }
            os << endl; //done, next line
        }
        else { //more nodes on this level, get the next one and continue enq children and printing
                curr = currLevel.front->heap;
        }
    }
}

ifstream inf("input.txt");
ofstream outf("output.txt");

int main() {
    int arr[10] = {0};
    for(int i = 0; i < 10; i++) {
        inf >> arr[i];
    }
    for(int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    
    inf.close();
    outf.close();
    return 0;
}