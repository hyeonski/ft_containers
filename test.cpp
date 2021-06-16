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
	std::multimap<int, int> map;
	map.insert(std::pair<int, int>(1, 100));
	map.insert(std::pair<int, int>(1, 200));
	map.insert(std::pair<int, int>(1, 50));

	map.erase(1);
	for (std::multimap<int, int>::const_iterator iter = map.begin(); iter != map.end(); ++iter)
	{
		std::cout << iter->second << std::endl;
	}
}