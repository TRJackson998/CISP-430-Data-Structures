#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next = NULL;
};

//Queue FIFO
struct Queue {
    Node* front = NULL;
    Node* rear = NULL;
};

//enqueue (put @ rear)
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

//dequeue (take from front)
int dequeue(Queue &Q) {
    if(Q.front) {
        int val;
        Node* temp = Q.front;
        Q.front = Q.front->next;
        val = temp->value;
        delete temp;
        if(!Q.front) {
            Q.rear = Q.front;
        }
        return val;
    }
    else {
        return -1;
    }
}

struct Stack {
    Node* head = NULL;
};

int pop(Stack &S) {
    if(S.head) { //list exists
            Node* temp = S.head;
            S.head = S.head->next;
            return temp->value;
    }
    else {
        return -1;
    }
}

void push(Stack &S, int value) {
    Node* nn = new Node;
    nn->value = value;
    nn->next = S.head;
    S.head = nn;
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

void decendingRadix(int arr[], int arr_size) {
    Stack Buckets[10];
    int passes = maxDigits(max(arr, arr_size));
    int place = 1;
    for(int pass = 0; pass < passes; pass++) { //pass through ones place, tens place, etc
        int ibucket, iarray = 0;
        for(int i = arr_size - 1; i >= 0; i--) { //for each element of the array, baackwards
            ibucket = arr[i] / place % 10;
            push(Buckets[ibucket], arr[i]);
        }
        for(int i = 0; i < 10; i++) { //for each bucket
            int j;
            while(Buckets[i].head) {
                j = pop(Buckets[i]);
                arr[iarray] = j;
                iarray++;
            }
        }
        place *= 10;
    }
}

int main() {
    int arr[] = {15, 240, 1, 56, 562, 84, 7, 965, 72, 85, 17, 86, 45, 83};
    int arr_size = 14;
    ascendingRadix(arr, arr_size);
    cout << "Array in ascending order: ";
    for(int i = 0; i < arr_size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
    int barr[] = {15, 240, 1, 56, 562, 84, 7, 965, 72, 85, 17, 86, 45, 83};
    decendingRadix(barr, arr_size);
    cout << "Array in decending order: ";
    for(int i = arr_size - 1; i >= 0; i--) {
        cout << barr[i] << ", ";
    }
    return 0;
}