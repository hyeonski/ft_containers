#include <iostream>
#include "list.hpp"
#include <list>

#ifndef NS
# define NS ft
#endif

int main()
{
	{
		std::cout << "-------- list default constructor test --------" << std::endl;
		NS::list<int> list;
		std::cout << "is empty()?" << list.empty() << std::endl;
	}

	{
		std::cout << "--------- list fill constructor test --------" << std::endl;
		NS::list<int> list(5, 100);

		// iterator로 자료 보여주기 필요
		std::cout << "size(): " << list.size() << std::endl;
	}

	{
		std::cout << "--------- list push_back test --------" << std::endl;
		NS::list<int> list;

		std::cout << "before size(): " << list.size() << std::endl;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);
		list.push_back(4);
		list.push_back(5);
		list.push_back(6);
		// iterator로 자료 보여주기 필요
		std::cout << "after size(): " << list.size() << std::endl;
	}

	{
		std::cout << "--------- list push_front test --------" << std::endl;
		NS::list<int> list;

		std::cout << "before size(): " << list.size() << std::endl;
		list.push_front(1);
		list.push_front(2);
		list.push_front(3);
		list.push_front(4);
		list.push_front(5);
		list.push_front(6);
		// iterator로 자료 보여주기 필요
		std::cout << "after size(): " << list.size() << std::endl;
	}

	{
		std::cout << "--------- list pop_back test --------" << std::endl;
		NS::list<int> list;

		list.push_back(1);
		list.push_back(2);
		list.push_back(3);
		list.push_back(4);
		list.push_back(5);
		list.push_back(6);
		
		std::cout << "before size(): " << list.size() << std::endl;
		list.pop_back();
		// iterator로 자료 보여주기 필요
		std::cout << "after size(): " << list.size() << std::endl;
	}

	{
		std::cout << "--------- list pop_front test --------" << std::endl;
		NS::list<int> list;

		list.push_back(1);
		list.push_back(2);
		list.push_back(3);
		list.push_back(4);
		list.push_back(5);
		list.push_back(6);
		
		std::cout << "before size(): " << list.size() << std::endl;
		list.pop_front();
		// iterator로 자료 보여주기 필요
		std::cout << "after size(): " << list.size() << std::endl;
	}

	{
		std::cout << "--------- list clear test --------" << std::endl;
		NS::list<int> list;

		list.push_back(1);
		list.push_back(2);
		list.push_back(3);
		list.push_back(4);
		list.push_back(5);
		list.push_back(6);
		
		std::cout << "before size(): " << list.size() << std::endl;
		list.clear();
		// iterator로 자료 보여주기 필요
		std::cout << "after size(): " << list.size() << std::endl;
		std::cout << "is empty? " << list.empty() << std::endl;
	}
}
