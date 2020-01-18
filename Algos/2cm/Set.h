#ifndef INC_2_SET_H
#define INC_2_SET_H
#include <iostream>
#include <time.h>
#endif //INC_2_SET_H

using namespace std;

class Set{
private:
    static int N;
    int n;
    char S, *A;
public:
    Set operator | (const Set&) const;
    Set & operator |= (const Set&);
    Set & operator = (const Set&);
    void show();
    int power() {return n;};
    Set(char S1 = '\0'){
        n = 0;
        A = nullptr;
        S = S1;
    }
    void generator(){
        int wA = 0;
        wA = rand() % 0xFFFF;
        A = new char (N);
        for (int i = 0; i < N - 1; i++){
            if ((wA >> i) & 1){
                A[n++] = (char)(i <= 9 ? i + '0' : i + 'A' - 10);
            }
        }
        A[n] = '\0';
    }
    ~Set(){delete [] A;}
};

int Set :: N = 16;

Set & Set::operator |=(const Set & B){
    for(int i = 0; i < B.n; ++i){
        bool f = true;
        for(int j = 0; j < n; ++j){
            if (B.A[i] == A[j]) f = false;
        }
        if(f) A[n++] = B.A[i];
    }
    A[n] = 0;
    return *this;
}
Set Set::operator | (const Set & B) const{
    Set C(*this);
    return (C |= B);
}

Set & Set::operator = (const Set &B){
    if(this != &B){
        n = B.n;
        S = 'R';
        A = new char (B.n);
        int i = 0;
        for(;i < n; i++){
            A[i] = B.A[i];
        }
    }
    return *this;
}

void Set::show(){
    std::cout << this->S << " =[" << A << "]" << std::endl;
}