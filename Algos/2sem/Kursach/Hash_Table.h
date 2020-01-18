#ifndef LAB_3_HASH_TABLE_H
#define LAB_3_HASH_TABLE_H
#endif //LAB_3_HASH_TABLE_H
#include <set>
#include <random>
#include <string.h>
#include <vector>
#include <list>
#include <unordered_set>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <chrono>

using std::sort;

enum{max_num = 1000};
using namespace std;

class Hash{
    char Name;
    unordered_set<int> table;
    vector<int> keys;
    int N, n_table;
public:
    Hash& operator = (const Hash & B){
        (*this).del();
        (*this).N =  B.N;
        for(auto i: B.table) table.insert(i);
        for(auto i: B.keys) keys.push_back(i);
        return (*this);
    };
    void create(char Name_set, int _N);
    Hash(){};
    Hash (const Hash &);
    Hash(Hash &&);
    Hash MERGE(Hash );
    Hash CONCAT(Hash );
    Hash SUBST(Hash , int k);
    Hash  operator& (const Hash &B) const{
        Hash R(*this);
        return R &= B;
    };
    Hash& operator &= (const Hash &);
    Hash  operator | (const Hash &B) const{
        Hash R(*this);
        return R |= B;
    };
    Hash& operator |= (const Hash &);
    Hash  operator + (const Hash &B) const{
        Hash R = (*this) & B;
        Hash A = (*this) | B;
        return R / B;
    };
    Hash operator / (const Hash &B) const{
        Hash R(*this);
        return R /= B;
    };
    Hash &operator /= (const Hash &);
    void del();
};

Hash::Hash(Hash && B):N(B.N), table(std::move(B.table)), keys(std::move(B.keys)) {};
Hash::Hash(const Hash &B): N(B.N){
    for(auto i: B.table) table.insert(i);
    for(auto i: B.keys) keys.push_back(i);
}

void Hash::create(char Name_set, int _N){
    (*this).N = _N;
    (*this).n_table = 3*N;
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

void Hash::del() {
    (*this).table.clear();
    (*this).keys.clear();
}

Hash& Hash::operator&=(const Hash & B) {
    for (auto i: (*this).table) {
        if(B.table.find(i) == B.table.end()){
            (*this).table.erase(i);
        }
    }
    return (*this);
}


Hash& Hash::operator|=(const Hash & B) {
    for(auto i: B.table){
        if((*this).table.find(i) == (*this).table.end()){
            (*this).table.insert(i);
        }
    }
    return (*this);
}


Hash& Hash::operator/=(const Hash & B) {
    for (auto i: (*this).table) {
        if(B.table.find(i) != B.table.end()){
            (*this).table.erase(i);
        }
    }
    return (*this);
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
