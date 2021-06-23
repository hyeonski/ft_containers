#include <iostream>
#include "list.hpp"
#include <list>
#include <vector>

#ifndef NS
# define NS ft
#endif

int main()
{
	{
		std::cout << "-------- list default constructor test --------" << std::endl;
		NS::list<int> list;
		std::cout << "is empty()?: " << list.empty() << std::endl;
	}

	{
		std::cout << "--------- list fill constructor-pointer test --------" << std::endl;
		int arr[] = {0, 1, 2, 3, 4};
		NS::list<int> list(arr, arr + 5);

		NS::list<int>::iterator iter = list.begin();
		(iter++)++;
		std::cout << "size(): " << list.size() << std::endl;
	}

	{
		std::cout << "--------- list fill constructor-iterator test --------" << std::endl;
		std::vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(4);
		vec.push_back(5);
		// iterator로 자료 보여주기 필요
		std::cout << "vector size(): " << vec.size() << std::endl;

		NS::list<int> list(vec.begin(), vec.end());

		// iterator로 자료 보여주기 필요
		std::cout << "list size(): " << list.size() << std::endl;
	}

	{
		std::cout << "--------- list fill constructor-value test --------" << std::endl;
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

	{
		std::cout << "--------- list assign-value test --------" << std::endl;
		NS::list<int> list;

		list.push_back(1);
		list.push_back(2);
		list.push_back(3);
		list.push_back(4);
		list.push_back(5);
		list.push_back(6);
		
		// iterator로 자료 보여주기 필요
		std::cout << "before size(): " << list.size() << std::endl;
		list.assign(3, 10);
		// iterator로 자료 보여주기 필요
		std::cout << "after size(): " << list.size() << std::endl;
	}

	{
		std::cout << "--------- list assign-pointer test --------" << std::endl;
		NS::list<int> list;
	
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);
		list.push_back(4);
		list.push_back(5);
		list.push_back(6);
		
		// iterator로 자료 보여주기 필요
		std::cout << "before size(): " << list.size() << std::endl;
		
		int arr[] = {0, 1, 2, 3, 4};
		list.assign(arr, arr + 5);
		// iterator로 자료 보여주기 필요
		std::cout << "after size(): " << list.size() << std::endl;
	}

	{
		std::cout << "--------- list assign-iterator test --------" << std::endl;
		NS::list<int> list;
	
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);
		list.push_back(4);
		list.push_back(5);
		list.push_back(6);
		
		// iterator로 자료 보여주기 필요
		std::cout << "before size(): " << list.size() << std::endl;

		std::vector<int> vec;
		vec.push_back(10);
		vec.push_back(9);
		vec.push_back(8);
		vec.push_back(7);
		vec.push_back(6);
		// iterator로 자료 보여주기 필요
		
		list.assign(vec.begin(), vec.end());
		// iterator로 자료 보여주기 필요
		std::cout << "after size(): " << list.size() << std::endl;
	}
}
