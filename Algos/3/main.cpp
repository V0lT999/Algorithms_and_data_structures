#include <iostream>
#include "Tree.h"

int main()
{
    int n = 0;
    Tree Tr('a','z', 4);
    srand(time(nullptr));
    Tr.MakeTree();
    if(Tr.exist()){
        Tr.OutTree();
        cout << '\n' << "Internal bypass: ";
        n = Tr.bypass();
        cout << '\n' << "Number of vertices having at least one child = " << n;
    }
    else cout << "Tree Is Empty!";
    cout << '\n' << "=== The End ===";
    //_getwch();
    return 0;
}