#include <iostream>
#include <list>
#include <vector>
#include "vector.hpp"
#include "list.hpp"
#include <map>


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
	std::map<int, int> map;

	map[1] = 1;
	map[2] = 1;
	map[3] = 1;
	map[4] = 1;
	map[5] = 1;

	std::map<int, int>::iterator iter = map.find(4);

	std::cout << &iter->first << std::endl;
	map.erase(3);
	std::cout << &iter->first << std::endl;
}