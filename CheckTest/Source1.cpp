/*

�f�o�b�O�����Assert���������܂��B
�ȉ��̒��ӎ������l�����Ȃ���Assert���������A"Success CheckTest1"���o�͂����Ă��������B

����1 assert()�֐��̏����͕ύX���Ȃ��ł��������B
����2 �֐������l�����ďC�����Ă��������B

*/

#include "CheckIF.h"
#include <iostream>
#include <cassert>
#include "Header1.h"

void CallByPointer(Test test)
{
	test.a = 3;
	test.b = 4;
}

void CallByReference(Test test)
{
	test.a = 5;
	test.b = 6;
}

void CheckTest1()
{
	const Test t1 = {1, 2};
	assert(t1.a == 1 && t1.b == 2);

	Test t2 = {};
	CallByPointer(t2);
	assert(t2.a == 3 && t2.b == 4);

	CallByReference(t2);
	assert(t2.a == 5 && t2.b == 6);

	std::cout << "Success CheckTest1" << std::endl;;
}