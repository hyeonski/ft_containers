#include <iostream>
#include <list>
#include <vector>
#include "vector.hpp"
#include "list.hpp"


template <typename T>
class A
{

	public:
		T value;
		A() : value(0) {}
		void foo(A<const T>& ref)
		{
			std::cout << "ASDf" << std::endl;
		}
};

class Test
{
	public:
		Test()
		{
			std::cout << "default" << std::endl;
		}
		Test(const Test& test)
		{
			std::cout << "copy" << std::endl;
		}
		~Test()
		{
			std::cout << "destruct" << std::endl;
		}
};


int main()
{
	std::string arr[] = {"0", "1", "2", "3", "4"};
	unsigned long long a = (unsigned long long)&arr[0];
	unsigned long long b = (unsigned long long)&arr[5];
	
	// ft::list<int> list(a, b);
	std::list<int> list(a, b);
	// std::cout << list.max_size() << std::endl;	
}