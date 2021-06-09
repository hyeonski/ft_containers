#include <iostream>
#include "list.hpp"
#include <list>

int main()
{
	ft::list<int> list;
	ft::list<int> fill_test(5, 100);

	list.push_back(3);
	list.push_back(3);
	list.push_back(3);
	list.push_back(3);
	list.push_back(3);
	list.push_back(3);

	ft::list<int> test;
	test.push_front(3);
	test.push_front(3);
	list.push_back(3);
	test.push_front(3);
	test.push_front(3);
	list.push_back(3);
	test.push_front(3);
	test.push_front(3);

	std::list<int> a;
	a.pop_back();
}
