#include <iostream>
#include "Tree.h"
#include <time.h>


int main(){
    srand(time(0));
    Tree A, B, C, D, E, R, B_and_C;
    R.create('R');
    A.create('A');
    B.create('B');
    C.create('C');
    D.create('D');
    E.create('E');
    A.Out();
    B.Out();
    C.Out();
    D.Out();
    E.Out();
    R = B & C;
    R.Out("B & C: ");
    R = R | D;
    R.Out("(B & C) | D: ");
    R = R + E;
    R.Out("(B & C) | D + E: ");
    R = A / R;
    R.Out("A / (B & C) | D + E: ");
    return 0;
}
