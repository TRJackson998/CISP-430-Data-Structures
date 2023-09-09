#include <iostream>
#include <iomanip>
using namespace std;

struct Node {
    int value;
    Node* next = NULL;
};

struct Queue {
    Node* front = NULL;
    Node* rear = NULL;
};

void enqueue(Queue &Q, int value) {
    Node* nn = new Node;
    nn->value = value;
    nn->next = NULL;

    if(!Q.front) { //queue is empty, currently front = rear = NULL
        Q.front = Q.rear = nn;
    }

    else { //queue is not empty
        Q.rear->next = nn;
        Q.rear = nn;
    }
}

void printQ(Queue Q) {
    Node* curr = Q.front;
    while(curr && curr != Q.rear) {
        cout << setw(2) << curr->value << ", ";
        curr = curr->next;
    }
    if(curr = Q.rear) {
        cout << curr->value << endl;
    }
}

Queue merge(Queue left, Queue right) {
    Queue merged;
    Node* i = left.front;
    Node* j = right.front;
    Node* k;
    

    while(i != NULL && j != NULL) {
        if(i->value <= j->value) {
            k = i;
            i = i->next;
        }
        else { // i->value > j->value
            k = j;
            j = j->next;
        }
        enqueue(merged, k->value);
        k = k->next;
    }

    while(i != NULL) {
        k = i;
        enqueue(merged, k->value);
        i = i->next;
        k = k->next;
    }
    while(j != NULL) {
        k = j;
        enqueue(merged, k->value);
        j = j->next;
        k = k->next;
    }
    return merged;
}

int nodeCount(Queue Q) {
    Node* curr = Q.front;
    int count = -1;
    while(curr) {
        count ++;
        curr = curr->next;
    }
    return count;
}

Node* midNode(Queue Q) {
    int num_nodes = nodeCount(Q);
    int mid = num_nodes / 2;
    Node* midNode = Q.front;
    for(int i = 0; i < mid; i++) {
        midNode = midNode->next;
    }
    return midNode;
}

//midNode becomes tail of first partition, midNode + 1 becomes head of second partition
void partition(Queue Q, Queue &leftPart, Queue &rightPart) {
    Node* mid = midNode(Q);
    leftPart.front = Q.front;
    leftPart.rear = mid;
    rightPart.front = mid->next;
    rightPart.rear = Q.rear;
    leftPart.rear->next = NULL;
}

void mergeSort(Queue &Q) {
    if(Q.front != Q.rear) {
        Queue left, right;
        partition(Q, left, right);
        mergeSort(left);
        mergeSort(right);
        Q = merge(left, right);
    }
}

int main() {
    Queue test1;
    enqueue(test1, 3);
    enqueue(test1, 5);
    enqueue(test1, 7);
    enqueue(test1, 6);
    enqueue(test1, 9);
    enqueue(test1, 2);
    enqueue(test1, 11);
    enqueue(test1, 8);
    enqueue(test1, 10);
    enqueue(test1, 1);
    enqueue(test1, 4);

    cout << "Before: ";
    printQ(test1);
    mergeSort(test1);
    cout << "After:  ";
    printQ(test1);
    return 0;
}