#include <iostream>

void foo()
{
	std::cout << "global" << std::endl;
}

class A
{
	public:
		void foo()
		{
			std::cout << "A foo" << std::endl;
		}
};

class B : public A
{
	public:
		void bar()
		{
			foo();
		}
};


int main()
{
	B b;
	b.bar();
}


