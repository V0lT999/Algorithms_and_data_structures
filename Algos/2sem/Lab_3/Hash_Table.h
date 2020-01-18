#ifndef LAB_3_HASH_TABLE_H
#define LAB_3_HASH_TABLE_H
#endif //LAB_3_HASH_TABLE_H
#include <set>
#include <random>
#include <time.h>
#include <string.h>
#include <vector>
#include <list>

enum{N = 10, max_num = 100, n_table = 30};
using namespace std;

class Hash{
    char Name;
    //vector<vector<int>> table;
    vector<list<int>> table;

    vector<int> keys;

public:
    void create(char Name_set);
    bool proof(int a);
    void Out();
    void Out(string _name);
    Hash  operator& (Hash );
    Hash  operator &= (Hash );
    Hash  operator | (Hash );
    Hash  operator |= (Hash );
    Hash  operator + (Hash );
    Hash  operator += (Hash );
    Hash  operator / (Hash );
    Hash  operator /= (Hash );
};

void Hash::create(char Name_set){
    Name = Name_set;
    (*this).table.resize(n_table);
    for (int i = 0; i < N; i++){
        int a = rand() % max_num;
        while(!proof(a)){
            a = rand() % max_num;
        }
    }
};

bool Hash::proof(int a){
    int func = (29*a + 2) % (3*N);
    (*this).keys.push_back(func);
    if(table[func].empty()){
        table[func].push_back(a);
        return true;
    } else{
        bool flag = false;
        for(auto i: table[func]){
            if(i == a) flag = true;
        }
        if (!flag){
            table[func].push_back(a);
            return true;
        } else return false;
    }
}

void Hash::Out(){
    cout << Name << ": ";
    for (int i = 0; i < 3*N; i++){
        cout << "[";
        for(auto j:table[i]){
            cout << j << " ";
        }
        cout << "]";
    }
    cout << endl;
}

void Hash::Out(string _name) {
    cout << _name << ": ";
    for (int i = 0; i < 3*N; i++){
        //cout << "[";
        for(auto j:table[i]){
            cout << j << " ";
        }
        //cout << "]";
    }
    cout << endl;
}

Hash Hash::operator&(Hash B) {
    Hash R(*this);
    return R &= B;
}

Hash Hash::operator&=(Hash B){
    for(auto i: keys){
        for(auto j: (*this).table[i]){
            bool flag = false;
            if(B.table[i].empty()){
                (*this).table[i].erase(table[i].begin(), table[i].end());
                flag = true;
            } else{
                for(auto j1: B.table[i]){
                    if(j == j1) flag = true;
                }
            }
            if(!flag){
                (*this).table[i].remove(j);
            }
        }
    }
    return (*this);
}

Hash Hash::operator|(Hash B) {
    Hash R(*this);
    return R |= B;
}

Hash Hash::operator|=(Hash B) {
    for(auto i: B.keys){
        for(auto j: B.table[i]){
            bool flag = false;
            if((*this).table[i].empty()){
                (*this).table[i].assign(B.table[i].begin(),B.table[i].end());
                flag = true;
            } else{
                for(auto j1: (*this).table[i]){
                    if(j == j1) flag = true;
                }
            }
            if(!flag){
                (*this).table[i].push_back(j);
            }
        }
    }
    return (*this);
}

Hash Hash::operator/(Hash B) {
    Hash R(*this);
    return R /= B;
}


Hash Hash::operator/=(Hash B) {
    for(auto i: keys){
        for(auto j: (*this).table[i]){
            bool flag = false;
            for(auto j1: B.table[i]){
                if(j == j1) flag = true;
            }
            if(flag){
                (*this).table[i].remove(j);
            }
        }
    }
    return (*this);
}

Hash Hash::operator+(Hash B) {
    Hash R(*this);
    return R += B;
}

Hash Hash::operator+=(Hash B) {
    Hash A = (*this) | B;
    Hash C = (*this) & B;
    return A / C;
}

