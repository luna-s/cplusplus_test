#include <iostream>
#include <cstdio>




















void* operator new(size_t size)
{
	if (!size)
		return NULL;

	void *p = malloc(size);
	if (!p)
		return NULL;

	std::cout << p << "  I'm overriding new " << std::endl;

	return p;
}

void* operator new[](size_t size)
{
	return operator new(size);
}

void* operator new(size_t size, const char* file, const int line)
{
	if (!size)
		return NULL;

	void *p = malloc(size);
	if (!p)
		return NULL;

	std::cout << p << "  I'm overriding new 222" << std::endl;

	return p;
}

void* operator new[](size_t size, const char* file, const int line)
{
	return operator new(size, file, line);
}

void operator delete(void* ptr)
{
	std::cout << ptr << "  I'm overriding delete " << std::endl;

	if (!ptr)
		return;

	free(ptr);
}

void operator delete[](void* ptr)
{
	return operator delete(ptr);
}

#define new new(__FILE__, __LINE__)

void main()
{
	int *a = new int;
	delete a;


	float *b = new float;
	delete b;

	char *c = new char[10];
	delete[] c;


	std::string *d = new std::string;
	delete d;

	std::string *e = new std::string("korea");
	delete e;


	
	
	
	




}