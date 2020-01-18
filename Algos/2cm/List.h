#ifndef INC_2_LIST_H
#define INC_2_LIST_H
#include <iostream>
#include  <time.h>
#endif //INC_2_LIST_H

using namespace std;

struct list{
    char a;
    list *next;
    list(char b = '\0', list *ne = nullptr){
        a = b;
        next = ne;
    }
    ~list(){
        delete next;
    }
};

class Set{
private:
    static int N;
    int n;
    char S;
public:
    list *A = nullptr;
    list *A1 = A;
    Set & operator | (Set&);
    Set & operator |= (Set&);
    Set & operator = (const Set &);
    void show();
    int power() {return n;};
    Set(char S = '\0'){
        cout << "Create " << S << endl;
        this->S = S;
        n = 0;
        A = nullptr;
    }
    void generator(){
        int wA = 0;
        wA = rand() % 0xFFFF;
        for (int i = 0; i < N - 1; i++){
            if ((wA >> i) & 1){
                A = new list((char)(i <= 9 ? i + '0' : i + 'A' - 10),A);
                n++;
            }
        }
        A1 = A;
        cout << "generated: ";
        this->show();
    }
    ~Set(){
        cout << "delete: " << this->S << endl;
        delete A;
    }
};

int Set :: N = 16;

Set & Set::operator |=(Set & B){
    cout << "Operator |= got: ";
    this->show();
    cout << " & ";
    B.show();
    while(B.A != nullptr){
        bool f = true;
        while(A != nullptr){
            if (B.A->a == A->a) f = false;
            A = A->next;
        }
        if(f) {
            A1 = new list (B.A->a,A1);
        }
        A = A1;
        B.A = B.A->next;
    }
    B.A = B.A1;
    cout << "return: ";
    this->show();
    return *this;
}

Set & Set::operator | (Set & B){
    cout << "operator | got: ";
    this->show();
    cout << " & ";
    B.show();
    Set C(*this);
    return (C |= B);
}

Set & Set::operator = (const Set &B){
    cout << "operator = got: ";
    this->show();
    cout << " & ";
    Set B11 = B;
    B11.show();
    cout << endl;

    if(this != &B){
        list *B1 = B.A;
        n = B.n;
        S = 'R';
        A = nullptr;
        while(B1 != nullptr){
            A = new list(B1->a,A);
            B1 = B1->next;
        }
    }
    this->A1 = this->A;
    cout << "return: ";
    this->show();
    return *this;
}

void Set::show(){
    cout << S << " = [";
    while (A != nullptr){
        cout << A->a;
        A = A->next;
    }
    A = A1;
    cout << "]" << endl;
}