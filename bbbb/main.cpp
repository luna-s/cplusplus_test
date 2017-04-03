#include <iostream>
#include "newh.h"

#if 0
void Test2()
{
	int *aaa = new int;
	
	double *bbb = new double;

	lunas::g_heap_manager.printInfo();
	
	char *ccc = new char[10];

	lunas::g_heap_manager.printInfo();

	delete aaa;
	delete bbb;
	
	lunas::g_heap_manager.printInfo();

	delete[] ccc;
}

void Test3()
{
	for (int i = 1; i < 100; ++i) {
		int *a = new int;
		delete a;

		char *b = new char[100];
		delete[] b;

		//delete[] a;

		lunas::g_heap_manager.printInfo();
	}
}

class TestXY
{
public:
	int x_;
	int y_;

public:
	TestXY() {};
	~TestXY() {};
};

void Test4()
{
	int *a = new int;
	int *b = new int[10];

	lunas::g_heap_manager.printInfo();
	char *c = new char[100];

	lunas::g_heap_manager.printRemain();
	delete a;
	
	delete[] b;

	lunas::g_heap_manager.printRemain();
	delete[] c;
	lunas::g_heap_manager.printRemain();

	TestXY *test = new TestXY();
	test->x_ = 10;
	test->y_ = 20;
	lunas::g_heap_manager.printRemain();
	delete test;
	lunas::g_heap_manager.printRemain();
	lunas::g_heap_manager.printInfo();

	a = NULL;
	delete a;

	lunas::g_heap_manager.printInfo();
}

#endif

void Test5()
{
	std::string *name = new std::string("korea");

	//lunas::g_heap_manager.printInfo();

	delete name;

	//lunas::g_heap_manager.printInfo();
}



void main()
{
	Test5();

	std::cout << "end" << std::endl;

	return;
}