#include <iostream>
#include "Hash_Table.h"

int main(){
    srand(time(0));
    Hash A, B, C, D, E, R, B_and_C;
    ofstream fout;
    fout.open("tests.txt");
    fout << 20 << endl;
    for(int i = 10; i < 133; i = i + 1){
        cout << i << endl;
        A.create('A',i);
        B.create('B',i);
        C.create('C',i);
        D.create('D',i);
        E.create('E',i);
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        R = B & C;
        R = R | D;
        R = R + E;
        R = A / R;
        R = A.MERGE(B);
        R = A.CONCAT(B);
        R = A.SUBST(B, 3);
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        if(time.count() == 0){
            i = i - 1;
        } else fout << i << ' ' << time.count() << endl;
        A.del();
        B.del();
        C.del();
        D.del();
        E.del();
        R.del();
    }
    fout.close();
    return 0;
}