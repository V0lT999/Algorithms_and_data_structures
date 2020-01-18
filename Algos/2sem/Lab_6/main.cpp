#include <iostream>
#include "Hash_Table.h"

int main(){
    srand(time(0));
    Hash A, B, C, D, E, R, B_and_C;
    A.create('A');
    B.create('B');
    C.create('C');
    D.create('D');
    E.create('E');
    R.create('R');
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
    R = A.MERGE(B);
    R.Out_id("A.MERGE(B): ");
    R = A.CONCAT(B);
    R.Out_id("A.CONCAT(B): ");
    R = A.SUBST(B, 3);
    R.Out_id("A.SUBST(B): ");
    return 0;
}