#include <iostream>
#include "source/Hash.h"
int main() {
    srand(time(0));
    HashMap A('A');
    HashMap B(A);
    A.add(12);
    whatHave(A);
    whatHave(B);
    return 0;
}