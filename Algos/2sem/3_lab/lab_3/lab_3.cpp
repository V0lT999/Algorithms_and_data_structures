#include "pch.h"
#include <iostream>
#include "Hash.h"

int main()
{
	srand(time(0));
	Hash_table A;
	Hash_table B;
	Hash_table C;
	Hash_table D;
	Hash_table E;
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