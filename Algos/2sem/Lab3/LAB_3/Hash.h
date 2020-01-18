#pragma once
#include <iostream>
#include <set>


using namespace std;
enum {N = 10};

struct _set
{
	set <int> keys;
};

class Hash
{
	char name;
	_set values[N];
	int Hash_func(int x) {
		int a = 7;
		int b = 1;
		return (a * x + b) % N;
	}
public:
	void create_table(char _name);
	void output();

};

void Hash::create_table(char _name)
{
	name = _name;
	for (int i = 0; i < N; i++) {
		int key = rand() % 100;
		values[Hash_func(key)].keys.insert(key);
	}
}

void Hash::output()
{
	cout << name << ": ";
	for (int i = 0; i < N; i++) {
		set<int>::iterator x = values[i].keys.begin();
		cout << "[ ";
		for (x; x != values[i].keys.end(); x++) {
			cout << *x << ' ';
		}
		cout << "] ";
	}
	cout << endl;
}

