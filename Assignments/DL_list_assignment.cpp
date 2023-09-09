#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct Node {
    string value;
    Node* prev;
    Node* next;
};

void traverse(Node* curr, ostream &os) {
    while(curr) {
        os << curr->value << endl;
        curr = curr->next;
    }
}

void rtraverse(Node* curr, ostream &os) { //reverse traverse
    while(curr) {
        os << curr->value << endl;
        curr = curr->prev;
    }
}

void rmNode(string value, Node* &head_alias, Node* &tail_alias) {
    if(head_alias) {//there is something in the list to delete
        Node* curr = head_alias;
        while((curr->value != value) && (curr->next)) {
            curr = curr->next;
        }
        if(curr->value == value) {//curr is on the node we want to delete
            Node* temp;
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
        else {
            //do nothing
        }
    }
}

bool isDuplicate(string value, Node* &head_alias, Node* &tail_alias) {
    Node* curr = head_alias;
    while(curr) {
        if(value == curr->value) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void orderedAdd(string value, Node* &head_alias, Node* &tail_alias) {
    if(!isDuplicate(value, head_alias, tail_alias)) { //only add it if it's not a duplicate
        Node* newNode = new Node;
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
                Node* curr = head_alias;
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

}

void str_tolower(string &value) {
    for(int i = 0; value[i]; i++) {
        if (value[i] < 'a') {
            value[i] = value[i] - ('A' - 'a');
        }
    }
}

void capitalize(Node* &head) {
    Node* curr = head;
    while(curr) {
        curr->value[0] = curr->value[0] - ('a' - 'A');
        curr = curr->next;
    }
}

ifstream inf("input.txt");
ofstream outf("output.txt");

int main() {
    //initialize the list
    Node* list_head = NULL;
    Node* list_tail = NULL;

    //get in the names
    string name;
    inf >> name;
    str_tolower(name);
    while(!inf.eof()) {
        if(name == "delete") {
            inf >> name;
            str_tolower(name);
            rmNode(name, list_head, list_tail);
        }
        else {
            orderedAdd(name, list_head, list_tail);
        }
        inf >> name;
        str_tolower(name);
    }

    capitalize(list_head);
    traverse(list_head, outf);
    outf << setfill('=') << setw(15) << "\n";
    rtraverse(list_tail, outf);

    inf.close();
    outf.close();
    return 0;
}
