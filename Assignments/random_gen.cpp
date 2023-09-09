#include <fstream>
#include <random>
using namespace std;

int main() {
    ofstream ofs("input.txt");
    int num;
    for(int i = 0; i < 100; i++) {
        num = rand() % 100;
        ofs << num << " ";
    }


}