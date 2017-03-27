#include <iostream>

class Animal
{
public:
	void Sound()
	{
		std::cout << "家府甫 郴促" << std::endl;
	}
};

class Dog : public Animal
{
public:
	void Sound()
	{
		std::cout << "港港" << std::endl;
	}
};

class Cat : public Animal
{
public:
	void Sound()
	{
		std::cout << "具克" << std::endl;
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