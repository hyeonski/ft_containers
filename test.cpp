#include <iostream>
#include <list>
#include <vector>
#include "vector.hpp"
#include "list.hpp"
#include <map>
#include <set>


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
	std::multimap<int, int> map;

	map.insert(std::pair<int, int>(1, 1));
	map.insert(std::pair<int, int>(1, 2));
	map.insert(std::pair<int, int>(1, 3));
	map.insert(std::pair<int, int>(1, 1));

	// std::map<int, int>::iterator iter = map.find(4);

	// std::cout << &iter->first << std::endl;
	map.erase(1);

	std::cout << map.empty() << std::endl;
}