#include "pch.h"
#include <time.h>
#include <iostream>
#include <cstring>

using namespace std;

enum { max_arr = 17, max_arr_res = 68, experiment  = 1000000};

void Randomize(char Arr[]) {
	int wA = 0;
	wA = rand() % 0xFFFF;
	for (int i = 0, k = 0; i < max_arr - 1; i++)
		if ((wA >> i) & 1)
			Arr[k++] = (char)(i <= 9 ? i + '0' : i + 'A' - 10);
}

struct mas {
	char a;
	mas *next;

	mas(char b = '\0', mas *p = nullptr) {
		next = p;
		a = b;
	}
	~mas() {
		delete next;
	}
};

void out(mas *p) {
	while (p != nullptr) {
		cout << p->a << " ";
		p = p->next;
	}
	cout << endl;
}

bool check(mas *p, char a) {
	while (p != nullptr && p->a != a) {
		p = p->next;
	}
	return (p) ? true : false;
}

int main() {
	srand(time(nullptr));
	char a[max_arr] = {}, b[max_arr] = {}, c[max_arr] = {}, d[max_arr] = {}, res_1[max_arr_res] = {};
	/*std::cin.getline(a, 16,'\n');
	std::cin.getline(b, 16,'\n');
	std::cin.getline(c, 16,'\n');
	std::cin.getline(d, 16,'\n');*/

	// - - - - - - - ARRAYS - - - - - - - - - -

	Randomize(a);
	Randomize(b);
	Randomize(c);
	Randomize(d);

	cout << "Generated array A: ";
	cout << a << endl;

	cout << "Generated array B: ";
	cout << b << endl;

	cout << "Generated array C: ";
	cout << c << endl;

	cout << "Generated array D: ";
	cout << d << endl;

	int k = 0; // 1.1 array;
	bool flag;
	unsigned long t1 = clock();
	for (int i = 0; i < experiment; i++) {
		for (int i = 0; a[i] != '\0'; i++) {
			res_1[i] = a[i];
			k++;
		}

		for (int i = 0; b[i] != '\0'; i++) {
			flag = false;
			for (int i1 = 0; i1 < k && !flag; i1++) {
				if (b[i] == res_1[i1]) {
					flag = true;
				}
			}
			if (!flag) {
				res_1[k++] = b[i];
			}
		}

		for (int i = 0; c[i] != '\0'; i++) {
			flag = false;
			for (int i1 = 0; i1 < k && !flag; i1++) {
				if (c[i] == res_1[i1]) {
					flag = true;
				}
			}
			if (!flag) {
				res_1[k++] = c[i];
			}
		}

		for (int i = 0; d[i] != '\0'; i++) {
			flag = false;
			for (int i1 = 0; i1 < k && !flag; i1++) {
				if (d[i] == res_1[i1]) {
					flag = true;
				}
			}
			if (!flag) {
				res_1[k++] = d[i];
			}
		}
	}

	unsigned long t2 = clock();
	unsigned long t = t2 - t1;

	cout << "Result array: " << res_1 << endl;

	cout << "Array time = " << t << endl;

	mas *A = new mas(a[0]);
	mas *B = new mas(b[0]);
	mas *C = new mas(c[0]);
	mas *D = new mas(d[0]);
	mas *res = nullptr;


	for (int i = 1; a[i] != '\0'; i++) {
		A = new mas(a[i], A);
	}

	for (int i = 1; b[i] != '\0'; i++) {
		B = new mas(b[i], B);
	}

	for (int i = 1; c[i] != '\0'; i++) {
		C = new mas(c[i], C);
	}

	for (int i = 1; d[i] != '\0'; i++) {
		D = new mas(d[i], D);
	}

	// - - - - - - - - LIST - - - - - - - - - - - - 
	mas *delA = A;
	mas *delB = B;
	mas *delC = C;
	mas *delD = D;

	cout << "Work with list" << endl;
	t1 = clock();
	for (int i = 0; i < experiment; i++) {
		A = delA;
		B = delB;
		C = delC;
		D = delD;
		res = nullptr;

		for (A; A != nullptr; A = A->next) { //1.1 list;
			res = new mas(A->a, res);
		}

		for (B; B != nullptr; B = B->next) {
			if (!check(res, B->a)) {
				res = new mas(B->a, res);
			}
		}

		for (C; C != nullptr; C = C->next) {
			if (!check(res, C->a)) {
				res = new mas(C->a, res);
			}
		}

		for (D; D != nullptr; D = D->next) {
			if (!check(res, D->a)) {
				res = new mas(D->a, res);
			}
		}
		if(i != experiment - 1) delete res;
	}
	t2 = clock();
	t = t2 - t1;
	cout << "Result list: ";
	out(res);

	cout << "List time = " << t << endl;

	// - - - - - - - - - - BOOL ARRAYS - - - - - - - - - - 

	cout << "Work with boll arrays" << endl;

	bool vA[max_arr - 1] = { false };
	bool vB[max_arr - 1] = { false };
	bool vC[max_arr - 1] = { false };
	bool vD[max_arr - 1] = { false };
	bool vO[max_arr - 1] = { false };

	for (int i = 0; vA[i]; i++)
		vA[a[i] <= '9' ? a[i] - '0' : a[i] - 'A' + 10] = true;
	for (int i = 0; vB[i]; i++)
		vB[b[i] <= '9' ? b[i] - '0' : b[i] - 'A' + 10] = true;
	for (int i = 0; vC[i]; i++)
		vC[c[i] <= '9' ? c[i] - '0' : c[i] - 'A' + 10] = true;
	for (int i = 0; vD[i]; i++)
		vD[d[i] <= '9' ? d[i] - '0' : d[i] - 'A' + 10] = true;
	for (int i = 0; i < max_arr - 1; i++) {
		vO[i] = vA[i] || vB[i] || vC[i] || vD[i];
	}
	t1 = clock();
	for (int i = 0; i < experiment; i++) {
		for (int i = 0; i < max_arr - 1; i++) {
			vO[i] = vA[i] || vB[i] || vC[i] || vD[i];
		}
	}
	t2 = clock();
	t = t2 - t1;
	for (int i = 0, k = 0; i < max_arr - 1; i++)
		if (vO[i]) res_1[k++] = (char)(i <= 9 ? i + '0' : i + 'A' - 10);
	
	cout << "Result bool array: ";
	for (int i = 0;res_1[i] != '\0'; i++) {
		cout << res_1[i];
	}
	cout << endl << "Bool array time: " << t << endl;

	//- - - - - - - - - - -MACHINE WORD - - - - - - - - - 

	cout << "Work with Machine word" << endl;
	for (int i = 0; i < max_arr - 1; i++) {
		res_1[i] = 0;
	}

	short wA = 0, wB = 0, wC = 0, wD = 0;

	for (int i = 0; a[i]; i++)
		wA |= (1 << (a[i] <= '9' ? a[i] - '0' : a[i] - 'A' + 10));
	for (int i = 0; b[i]; i++)
		wB |= (1 << (b[i] <= '9' ? b[i] - '0' : b[i] - 'A' + 10));
	for (int i = 0; c[i]; i++)
		wC |= (1 << (c[i] <= '9' ? c[i] - '0' : c[i] - 'A' + 10));
	for (int i = 0; d[i]; i++)
		wD |= (1 << (d[i] <= '9' ? d[i] - '0' : d[i] - 'A' + 10));
	int wO = 0;

	cout << "Result: " << endl << "wA: " << wA << "\n" << "wB: " << wB << "\n" << "wC: " << wC << "\n" << "wD: " << wD << "\n";

	t1 = clock();
	for (int i = 0; i < experiment; i++) {
		wO = wA | wB | wC | wD;
	}
	t2 = clock();
	for (int i = 0, k = 0; i < max_arr - 1; i++)
		if ((wO >> i) & 1) res_1[k++] = (char)(i <= 9 ? i + '0' : i + 'A' - 10);
	t = t2 - t1;
	cout << "Result Machine word: ";
	for (int i = 0;res_1[i] != '\0'; i++) {
		cout << res_1[i];
	}

	cout << endl << "Machine word time: " << t << endl;

	delete res;
	delete delA;
	delete delB;
	delete delC;
	delete delD;

	std::cin.get();

	return 0;
}

