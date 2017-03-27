#include <iostream>

class Animal
{
public:
	void Sound()
	{
		std::cout << "�Ҹ��� ����" << std::endl;
	}
};

class Dog : public Animal
{
public:
	void Sound()
	{
		std::cout << "�۸�" << std::endl;
	}
};

class Cat : public Animal
{
public:
	void Sound()
	{
		std::cout << "�߿�" << std::endl;
	}
};

class DoCat : public Dog, Cat
{

};



void main(void)
{
	DoCat docat;

	docat.Sound();

	return;
}