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
#include <time.h>

using std::sort;

enum{N = 10, max_num = 100, n_table = 30};
using namespace std;

class Hash{
    char Name;
    unordered_set<int> table;
    vector<int> keys;
public:
    void create(char Name_set);
    void Out();
    void Out(string _name);
    void Out_id(string _name);
    Hash MERGE(Hash );
    Hash CONCAT(Hash );
    Hash SUBST(Hash , int k);
    Hash  operator& (Hash );
    Hash  operator | (Hash );
    Hash  operator + (Hash );
    Hash  operator / (Hash );
};

void Hash::create(char Name_set){
    (*this).Name = Name_set;
    for (int i = 0; i < N; i++){
        int a = rand() % max_num;
        while(table.find(a) != table.end()){
            a = rand() % max_num;
        }
        table.insert(a);
    }
    for(auto i: table){
        keys.push_back(i);
    }
};

void Hash::Out(){
    cout << Name << ": ";
    for(auto i: table){
        cout << i << ' ';
    }
    cout << endl;
}

void Hash::Out(string _name) {
    cout << _name << ": ";
    for(auto i: table){
        cout << i << ' ';
    }
    cout << endl;
}

void Hash::Out_id(string _name) {
    cout << _name;
    for(auto i: (*this).keys){
        cout << i << ' ';
    }
    cout << endl;
}

Hash Hash::operator&(Hash B) {
    Hash R(*this);
    for (auto i: R.table) {
        if(B.table.find(i) == B.table.end()){
            R.table.erase(i);
        }
    }
    R.keys.clear();
    for(auto i: R.table){
        R.keys.push_back(i);
    }
    return R;
}


Hash Hash::operator|(Hash B) {
    Hash R(*this);
    for(auto i: B.table){
        if(R.table.find(i) == R.table.end()){
            R.table.insert(i);
        }
    }
    R.keys.clear();
    for(auto i: R.table){
        R.keys.push_back(i);
    }
    return R;
}


Hash Hash::operator/(Hash B) {
    Hash R(*this);
    for (auto i: R.table) {
        if(B.table.find(i) != B.table.end()){
            R.table.erase(i);
        }
    }
    R.keys.clear();
    for(auto i: R.table){
        R.keys.push_back(i);
    }
    return R;
}

Hash Hash::operator+(Hash B) {
    Hash R = (*this) | B;
    Hash A = (*this) & B;
    R = R / A;
    R.keys.clear();
    for(auto i: R.table){
        R.keys.push_back(i);
    }
    return R;
}

Hash Hash::MERGE(Hash B) {
    Hash R(*this);
    R.table.insert(B.table.begin(), B.table.end());
    R.keys.insert(R.keys.end(), B.keys.begin(), B.keys.end());
    sort(R.keys.begin(), R.keys.end());
    return R;
}

Hash Hash::CONCAT(Hash B) {
    Hash R(*this);
    R.table.insert(B.table.begin(), B.table.end());
    R.keys.insert(R.keys.end(), B.keys.begin(), B.keys.end());
    return R;
}

Hash Hash::SUBST(Hash B, int k) {
    Hash R(*this);
    R.table.insert(B.table.begin(), B.table.end());
    R.keys.insert(R.keys.begin() + k, B.keys.begin(), B.keys.end());
    return R;
}
