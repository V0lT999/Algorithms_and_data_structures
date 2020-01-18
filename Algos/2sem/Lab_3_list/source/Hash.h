//
// Created by Nick on 04.03.2019.
//
#include <list>
#include <vector>
#include <cstdio>
#include <iostream>
#include <random>

using namespace std;
#ifndef LAB2_HASH_H
#define LAB2_HASH_H
class HashMap{

public:
    typedef unsigned short hashtype;
    HashMap() {
        table.resize(m);
        A = '0';
    }
    explicit HashMap(char i) : A(i) {
        table.resize(m);
        for (hashtype j = 0; j < m; ++j) {
          if(rand() % 2)  add(j);
        }
    }
    void add(hashtype val){
         table.at(hash_function(val)).push_back(val);
     }
    list<hashtype> get(hashtype key){
         return table.at(key);
     }
     void printTable();
    HashMap operator~() const;

    HashMap operator|(const HashMap &B) const;

    HashMap operator&(const HashMap &) const;

    HashMap operator^(const HashMap &B) const { return (~(*this & B) & (*this | B));};

    HashMap &operator=(const HashMap & copy){table = copy.table; return (*this);};

    friend void whatHave(HashMap &e);
private:
    static const hashtype a = 97;
    static const hashtype b = 11;
    static const hashtype capacity = 26;
    static const hashtype m = capacity * 3;
    static const hashtype MAXINT = 100;
    vector<list<hashtype> > table;
    static hashtype hash_function(hashtype x) {
        return (a * x + b) % m;
    }
    char A;
};
void HashMap::printTable() {

    printf("HashMap %c:\n",A);
        hashtype p = 0;
        for(auto & i : table){
            p++;
            if(!i.empty()){
            printf("key - %2d = {",p);
            for(auto j : i) {
                printf("%4d", j);
            }
            printf("  }\n");
            }
        }
    }

HashMap HashMap::operator~() const {
    HashMap C;
    for (hashtype i = 0; i < MAXINT; ++i) {
        if (table.at(hash_function(i)).empty())
            C.add(i);
        else {
            bool flag = true;
            for (auto a = table.at(hash_function(i)).begin(); a != table.at(hash_function(i)).end() && flag; a++)
                if (*a == i) flag = false;
            if (flag) C.add(i);
        }
    }


    return C;
}
HashMap HashMap::operator|(const HashMap &B) const {
    // if this == B return C(*this)
    HashMap C(*this);
    bool flag;
    for (hashtype i = 0; i < m; ++i) {
        if(!table.at(i).empty()) {
            for (auto c : B.table.at(i)) {
                flag = true;
                for (auto d : this->table.at(i)) {
                    if (c == d) {
                    flag = false;
                        break;
                    }
                }
                if(flag) C.add(c);
            }
        } else C.table.at(i) = B.table.at(i);
    }
    return C;
}
HashMap HashMap::operator&(const HashMap &B) const {
    HashMap C;
    bool flag;
    for (hashtype i = 0; i < m; ++i) {
        if(!table.at(i).empty() && !B.table.at(i).empty()) {
            for (auto c : B.table.at(i)) {
                flag = false;
                for (auto d : table.at(i)) {
                    if (c == d) {
                        flag = true;
                        break;
                    }
                }
                if (flag) C.add(c);
            }
        }
    }
    return C;
}
void whatHave(HashMap &e){
    for (HashMap::hashtype i = 0; i < HashMap::m; ++i)
        for (unsigned short &a : e.table.at(i))
            cout << a << " ";
    cout << endl;
}
#endif //LAB2_HASH_H
