#include <iostream>
#include <list>


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

		}
};

int main()
{
	std::list<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	list.push_back(6);
	std::list<int> list2;
	list2.push_back(7);
	list2.push_back(8);
	list2.push_back(9);

	for (auto iter = list.begin(); iter != list.end(); iter++)
		std::cout << *iter << std::endl;

	std::cout << std::endl;

	for (auto iter = list2.begin(); iter != list2.end(); iter++)
		std::cout << *iter << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	std::list<int>::reverse_iterator it(list.begin());
	it++;
	it++;
	std::cout << *it << std::endl;
	std::cout << *it.base() << std::endl;
}