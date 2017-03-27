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

class Pet : public Dog, public Cat
{

};



void main(void)
{
	Pet pet;

	pet.Cat::Sound();

	pet.Dog::Sound();

	return;
}