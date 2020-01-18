#include <iostream>
#include "Set.h"

const long q0 = 1;

int main() {
    srand(time(nullptr));
    Set A('A'), B('B'), C('C'), D('D'), E('E');
    A.generator();
    A.show();
    B.generator();
    B.show();
    C.generator();
    C.show();
    D.generator();
    D.show();
    clock_t t1 = clock();
    for(long q = 0; q < q0; q++) {
        E = A | B | C | D;
    }
    clock_t t2 = clock();
    E.show();
    cout << "Middle power = " << (A.power() + B.power() + C.power() + D.power() + E.power()) / 5 << endl;
    cout << "Time = " << t2 - t1 << "/" << q0 << endl;
    return 0;
}