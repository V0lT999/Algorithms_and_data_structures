#pragma once
#include <iostream>
#include <ctime>

enum {N = 10};

struct _list {
	int id;
	int count;
	_list *next;

	_list() : id(0), count(-1), next(nullptr) {}
	_list(int _id, int _count) : id(_id), count(_count), next(nullptr) {}
	~_list() {
		delete next;
	}
};

class Hash_table {
	char name;
	_list *list[N];

public:
	void create_table(char _name);
	void output();
	Hash_table operator & (const Hash_table &B);
	Hash_table &operator &= (const Hash_table &B);
};

void Hash_table::create_table(char _name)
{
	name = _name;
	for (int i = 0; i < N; i++) {
		list[i] = new _list();
	}
	for (int i = 0; i < N; i++) {
		int generate = rand() % 100;
		int index = (7 * generate + 1) % 10; //hash_func;
		if (list[index]->id != 0) {
			_list *buf = new _list();
			buf = list[index];
			while (buf->next != nullptr) {
				buf = buf->next;
			}
			buf->next = new _list(buf->id + 1, generate);
		}
		else {
			list[index]->id = 1;
			list[index]->count = generate;
		}
	}
}

void Hash_table::output()
{
	std::cout << name << ": ";
	for (int i = 0; i < N; i++) {
		_list *out = new _list();
		out = list[i];
		std::cout << "[ ";
		while (out->next != nullptr) {
			std::cout << out->count << ' ';
			out = out->next;
		}
		std::cout << out->count << ' ';
		std::cout << "] ";
	}
	std::cout << std::endl;
}

Hash_table Hash_table::operator & (const Hash_table &B)
{
	Hash_table C(*this);
	return C &= B;
}

Hash_table& Hash_table::operator &= (const Hash_table &B)
{
	Hash_table C(*this);
	for (int i = 0; i < N; i++) {
		_list *buf = new _list();
		buf = this->list[i];
		while (buf->next != nullptr) {
			_list *buf1 = new _list();
			buf1 = B.list[i];
			bool flag = false;
			while (buf1->next != nullptr) {
				if (buf->count == buf1->count) {
					flag = true;
				}
				buf1 = buf1->next;
			}
			if (buf->count == buf1->count) {
				flag = true;
			}
			if (flag == false) {

			}
		}
	}
}