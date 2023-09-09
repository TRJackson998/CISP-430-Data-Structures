#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node {
    int value;
    Node* next;
};

void push(Node* &top_alias, int value) {
    Node* nn = new Node;
    nn->value = value;
    nn->next = top_alias;
    top_alias = nn;
}

int pop(Node* &top) {
    if(top) { //stack exists
            int value = top->value;
            Node* temp = top;
            top = top->next;
            delete temp;
            return value;
    }
    else {
        return NULL;
    }
}

int to_int(char val) {
    int integ_val = static_cast<int>(val - '0');
    return integ_val;
}

ifstream inf("input.txt");                 //input.txt is the file that we read from

ofstream outf("output.txt");          //output.txt is the file that we write into

int main() {
    //initialize the stack
    Node* stack_top = new Node;

    //get in the postfix expression
    string expression;
    while(inf.good()) {
        inf >> expression;
    }

    //evaluate the expression char by char
    for(int i = 0; expression[i] ; i++) {
        //if it is a number
        if((expression[i] != '+') &&
           (expression[i] != '-') &&
           (expression[i] != '*') &&
           (expression[i] != '/')) {
               int val = to_int(expression[i]);
               push(stack_top, val);
           }

        //else it is an operation
        else {
            int lhs, rhs;
            rhs = pop(stack_top);
            lhs = pop(stack_top);

            switch (expression[i]) {
                case '+':
                    push(stack_top, lhs+rhs);
                    break;
                case '-':
                    push(stack_top, lhs-rhs);
                    break;
                case '*':
                    push(stack_top, lhs*rhs);
                    break;
                case '/':
                    if(rhs != 0) {
                        push(stack_top, lhs/rhs);
                    }
                    else {
                        cout << "Division by zero error.\n";
                    }
                    break;
            }
        }
    }

    //output the answer to the output file
    outf << stack_top->value;

    inf.close();
    outf.close();
    return 0;
}
