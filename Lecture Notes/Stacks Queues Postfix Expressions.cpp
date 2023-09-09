#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;
};


//Stack LIFO
//top, push, pop

void push(Node* &head_alias, int value) {
    Node* nn = new Node;
    nn->value = value;
    nn->next = head_alias;
    head_alias = nn;
}

Node* pop(Node* &head) {
    if(head) { //list exists
            Node* temp = head;
            head = head->next;
            return temp;
    }
}

//Queue FIFO
struct Queue {
    Node* front;
    Node* rear;
};


//enqueue (put @ rear)
void enqueue(Node* &Front, Node* &Rear, int value) {
    Node* nn = new Node;
    nn->value = value;
    nn->next = NULL;

    if(!Front) { //queue is empty, front = rear = NULL
        Front = Rear = nn;
    }
    else { //
        Rear->next = nn;
        Rear = nn;
    }
}

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
int dequeue(Node* &Front, Node* &Rear) {
    if(Front) {
        int val;
        Node* temp = Front;
        Front = Front->next;
        val = temp->value;
        delete temp;
        if(!Front) {
            Rear = Front;
        }
        return val;
    }
    else {
        return -1;
    }
}

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


int main() {
    //
    return 0;
}
