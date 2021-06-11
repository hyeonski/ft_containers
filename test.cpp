#include <iostream>
#include <list>

int main()
{
	std::list<int> list;

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);

	const std::list<int>::const_iterator iter = list.begin();

	std::cout << *iter << std::endl;	

	for (auto it = list.begin(); it != list.end(); it++)
		std::cout << *it << std::endl;
}