#include <iostream>
#include <list>
#include <vector>
#include "vector.hpp"
#include "list.hpp"
#include <map>
#include <set>
#include "map.hpp"
#include <stack>
#include "DequeIterator.hpp"

class A
{
	public:
		A()
		{
			std::cout << "default" << std::endl;
		}

		A(const A& a)
		{
			std::cout << "copy" << std::endl;
		}

		~A()
		{
			std::cout << "destruct" << std::endl;
		}
};

void func()
{
	ft::map<int, int> map;

}

int main()
{
	ft::DequeBlock<int> deque;
	// std::cout << "size: " << deque.size() << std::endl;

	// for (int i = 0; i < 30; ++i)
	// 	deque.insert(deque.begin(), i);
	// for (int i = 0; i < 20; ++i)
	// 	deque.erase(--deque.end());
	// std::cout << "size: " << deque.size() << std::endl;

	

	// ft::DequeBlock<int>::iterator iter = deque.begin();
	// for (; iter != deque.end(); ++iter)
	// 	std::cout << *iter << std::endl;

	// std::cout << deque.end() - deque.begin() << std::endl;

	deque.push_front(2);
	deque.push_front(1);
	deque.push_back(3);
	deque.push_back(4);
	deque.push_back(5);

	ft::DequeBlock<int>::iterator iter = deque.begin();
	iter++;
	iter++;

	std::cout << "size: " << deque.size() << std::endl;
	

	for (ft::DequeBlock<int>::iterator it = deque.begin(); it != deque.end(); ++it)
		std::cout << *it << std::endl;

	std::cout << std::endl << deque.end() - deque.begin() << std::endl;


	
}
