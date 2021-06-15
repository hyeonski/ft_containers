#include <iostream>
#include <list>
#include <vector>
#include "vector.hpp"


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

	std::vector<int> vec(7);
	std::cout << vec.size() << std::endl;
	std::cout << vec.capacity() << std::endl << std::endl;

	std::vector<int> test(vec);
	std::cout << test.size() << std::endl;
	std::cout << test.capacity() << std::endl << std::endl;

	std::vector<int> test2(vec.begin(), vec.end());
	std::cout << test2.size() << std::endl;
	std::cout << test2.capacity() << std::endl << std::endl;

	std::vector<int> test3;
	test3.assign(vec.begin(), vec.end());
	std::cout << test3.size() << std::endl;
	std::cout << test3.capacity() << std::endl << std::endl;

	vec.pop_back();
	vec.pop_back();

	std::vector<int> empty;
	empty = vec;
	std::cout << empty.size() << std::endl;
	std::cout << empty.capacity() << std::endl << std::endl;

	std::list<int> list(7);

	std::vector<int> good(list.begin(), list.end());
	std::cout << good.size() << std::endl;
	std::cout << good.capacity() << std::endl << std::endl;


	// for (std::vector<int>::const_iterator iter = vec.begin(); iter != vec.end(); ++iter)
	// 	std::cout << *iter << std::endl;

	
}