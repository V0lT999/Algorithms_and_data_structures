#include "pch.h"
#include <iostream>
#include <set>
#include "Hash.h"
#include <ctime>

int main()
{
	srand(time(0));
	Hash A;
	Hash B;
	Hash C;
	Hash D;
	Hash E;
	A.create_table('A');
	B.create_table('B');
	C.create_table('C');
	D.create_table('D');
	E.create_table('E');
	A.output();
	B.output();
	C.output();
	D.output();
	E.output();
	system("pause");
	return 0;
}