#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct Node {
    T value;
    Node<T>* prev;
    Node<T>* next;
};

//doubly linked list
//head and tail
//prev and next nodes

template <typename T>
struct doublyLinkedList {
    Node<T>* head;
    Node<T>* tail;
};


template <typename T>
void traverse(Node<T>* curr) {
    while(curr) {
        cout << curr->value << endl;
        curr = curr->next;
    }
}

template <typename T>
void rtraverse(Node<T>* curr) {
    while(curr) {
        cout << curr->value << endl;
        curr = curr->prev;
    }
}

template <typename T>
void rmNode(T value, Node<T>* &head_alias, Node<T>* &tail_alias) {
    if(head_alias) {//there is something in the list to delete
        Node<T>* curr = head_alias;
        while((curr->value != value) && (curr->next)) {
            curr = curr->next;
        }
        if(curr->value == value) {//curr is on the node we want to delete
            Node<T>* temp;
            if(curr->prev) {
                temp = curr->prev->next;
                curr->prev->next = curr->next;
            }
            else {
                head_alias = curr->next;
            }
            if(curr->next) {
                temp = curr->next->prev;
                curr->next->prev = curr->prev;
            }
            else {
                tail_alias = curr->prev;
            }
            delete temp;
        }
    }
}

template <typename T>
void orderedAdd(T value, Node<T>* &head_alias, Node<T>* &tail_alias) {
    Node<T>* newNode = new Node<T>;
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    if(!head_alias) {//nothing in the list yet
        head_alias = tail_alias = newNode;
    }
    else {//there is at least one node in the list
        if(value < head_alias->value) { //new node goes before the head
            head_alias->prev = newNode;
            newNode->next = head_alias;
            head_alias = newNode;
        }
        else if(value > tail_alias->value) { //new node goes after the tail
            tail_alias->next = newNode;
            newNode->prev = tail_alias;
            tail_alias = newNode;
        }
        else {
            Node<T>* curr = head_alias;
            while((curr->value) < value) {
                curr = curr->next;
            }//insert the new one before curr
            newNode->prev = curr->prev;
            newNode->next = curr;
            curr->prev->next = newNode;
            curr->prev = newNode;



        }
    }
}

template <typename T>
void add(Node<T>* &head_alias, T value) {  //adds node to beginning
    Node<T>* nn = new Node<T>;
    nn->value = value;
    nn->next = head_alias;
    head_alias = nn;
}

int main() {
    Node<string>* head = NULL;
    Node<string>* tail = NULL;
    string name1 = "Abe";
    string name2 = "Ben";
    string name3 = "Callum";
    string name4 = "Derek";
    orderedAdd(name2, head, tail);
    orderedAdd(name1, head, tail);
    orderedAdd(name4, head, tail);
    orderedAdd(name3, head, tail);
    traverse(head);
    cout << endl;
    rmNode(name2, head, tail);
    rmNode(name4, head, tail);
    //rmNode("Callum", head, tail);
    rtraverse(tail);



    return 0;
}
