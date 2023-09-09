#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T value;
    Node* next;
};

template <typename T>
void add(Node<T>* &head_alias, T value) {  //adds node to beginning
    Node<T>* nn = new Node<T>;
    nn->value = value;
    nn->next = head_alias;
    head_alias = nn;
}

template <typename T>
void traverse(Node<T>* curr) {
    while(curr) {
        cout << curr->value << endl;
        curr = curr->next;
    }
}

template <typename T>
void deleteNode(Node<T>* &head, T value) {
    if(head) { //list exists
            Node<T>* temp = head;
        if(value == head->value) { //first case, value is in first node, must update head pointer
            head = head->next;
            delete temp;
        }
        else { //second case, head doesn't change
            while((temp->next) && (temp->next->value != value)) {
                temp = temp->next;
            }
            if(temp->next) {
                Node<T>* trash = temp->next;
                temp->next = temp->next->next;
                delete trash;
            }
        }
    }
}

int main() {
    Node<int>* head = NULL;
    traverse(head);
    add(head, 10);
    add(head, 20);
    traverse(head);
}
