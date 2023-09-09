#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int main () {
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    string str1, str2, str3;
    while(!inf.eof()) {
        getline(inf, str1);
        outf << str1 << " ";

    }
    

}