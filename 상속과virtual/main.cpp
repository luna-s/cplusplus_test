#include<iostream>

using namespace std;

class Animal {
public:
	const char* print1() { return "Animal "; }
	virtual char* const print2() { return "Animal "; }
	const char* print3() { return "Animal "; }
};

class Cat : public Animal {
public:
	const char* print1() { return "Cat "; } //Override
	char* const print2() { return "Cat "; }
};

class Dog : public Animal {
public:
	const char* print1() { return "Dog "; }//Override
	char* const print2() { return "Dog "; }
};

void f1(Animal* a, Cat* c, Dog* d) {
	cout << a->print1() << c->print1() << d->print1() << endl;
}
void f2(Animal* a, Cat* c, Dog* d) {
	cout << a->print2() << c->print2() << d->print2() << endl;
}

void f3(Animal* a, Animal* c, Animal* d) {
	cout << a->print1() << c->print1() << d->print1() << endl;
}
void f4(Animal* a, Animal* c, Animal* d) {
	cout << a->print2() << c->print2() << d->print2() << endl;
}
void f5(Animal *a, Cat*c, Dog *d) {
	cout << a->print3() << c->print3() << d->print3() << endl;
}
void f6(Animal *a, Animal *c, Animal *d) {
	cout << a->print3() << c->print3() << d->print3() << endl;
}
int main() {
	Animal *a = new Animal();;
	Cat *c = new Cat();
	Dog *d = new Dog();;


	f1(a, c, d);
	f2(a, c, d);
	f3(a, c, d);
	f4(a, c, d);
	f5(a, c, d);
	f6(a, c, d);

}

