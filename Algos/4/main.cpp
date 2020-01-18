#include "graph.h"

int main() {
    Graph A;
    if(A.generator()){
        A.show();
        A.way();
        return 0;
    } else return 1;
}