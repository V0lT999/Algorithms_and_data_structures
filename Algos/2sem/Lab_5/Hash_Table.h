#ifndef LAB_3_HASH_TABLE_H
#define LAB_3_HASH_TABLE_H
#endif //LAB_3_HASH_TABLE_H
#include <set>
#include <random>
#include <time.h>
#include <string.h>
#include <vector>
#include <list>
#include <unordered_set>
#include <algorithm>

using std::sort;

enum{N = 10, max_num = 100, n_table = 30};
using namespace std;

class Hash{
    char Name;
    //unordered_set<int, int> table;
    vector<list<int>> table;
    vector<int> keys;
    vector<list<int>::iterator> table_id;
public:
    void create(char Name_set);
    bool proof(int a);
    void Out();
    void Out(string _name);
    void Out_table_id(string _name);
    void sort_id();
    int hash_table(int a);
    Hash MERGE(Hash );
    Hash CONCAT(Hash );
    Hash SUBST(Hash , int k);
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
    (*this).Name = Name_set;
    (*this).table.resize(n_table);
    for (int i = 0; i < N; i++){
        int a = rand() % max_num;
        while(!proof(a)){
            a = rand() % max_num;
        }
    }
    sort(keys.begin(), keys.end());
    int k = 0;
    for(auto i: (*this).keys){
        for(auto j: (*this).table[i]){
            for(int j1 = 0; j1 < table_id.size(); j1++){
                if(j == *table_id[j1]){
                    swap((*this).table_id[k],(*this).table_id[j1]);
                    k++;
                }
            }
        }
    }
};

bool Hash::proof(int a){
    int func = hash_table(a);
    if(table[func].empty()){
        (*this).keys.push_back(func);
        table[func].push_back(a);
        (*this).table_id.push_back(--(*this).table[func].end());
        return true;
    } else{
        bool flag = false;
        for(auto i: table[func]){
            if(i == a) flag = true;
        }
        if (!flag){
            table[func].push_back(a);
            (*this).table_id.push_back(--(*this).table[func].end());
            return true;
        } else return false;
    }
}

int Hash::hash_table(int a) {
    return (29*a + 2) % (3*N);
}

void Hash::sort_id() {
    for(int i = 0; i < (*this).table_id.size() - 1; i++){
        for(int j = i + 1; j < (*this).table_id.size(); j++){
            if(*(*this).table_id[i] > *(*this).table_id[j]){
                swap((*this).table_id[i], (*this).table_id[j]);
            }
        }
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

void Hash::Out_table_id(string _name) {
    cout << _name << ": ";
    for(auto i: (*this).table_id){
        cout << *i << ' ';
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

Hash Hash::MERGE(Hash B) {
    Hash R(*this);
    R.table.resize(2*R.table.size());
    for(int i = n_table; i < 2 * n_table; i++){
        R.table[i].assign(B.table[i - n_table].begin(),B.table[i - n_table].end());
    }
    R.table_id.resize(2*R.table_id.size());
    for(int i = N; i < 2*N; i++){
        R.table_id[i] = B.table_id[i - N];
    }
    R.sort_id();
    return R;
}

Hash Hash::CONCAT(Hash B) {
    Hash R(*this);
    R.table.resize(2*R.table.size());
    for(int i = n_table; i < 2 * n_table; i++){
        R.table[i].assign(B.table[i - n_table].begin(),B.table[i - n_table].end());
    }
    R.table_id.resize(2*R.table_id.size());
    for(int i = N; i < 2*N; i++){
        R.table_id[i] = B.table_id[i - N];
    }
    return R;
}

Hash Hash::SUBST(Hash B, int k) {
    Hash R(*this);
    R.table.resize(2*R.table.size());
    for(int i = n_table; i < 2 * n_table; i++){
        R.table[i].assign(B.table[i - n_table].begin(),B.table[i - n_table].end());
    }
    R.table_id.resize(2*R.table_id.size());
    /*for(int i = N; i < 2*N; i++){
        R.table_id[i] = B.table_id[i - N];
    }*/
    for(int i = k; i < N; i++){
        R.table_id[i + N] = R.table_id[i];
    }
    for(int i = 0; i < N; i++){
        R.table_id[i + k] = B.table_id[i];
    }
    return R;
}