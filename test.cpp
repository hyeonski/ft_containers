#include <iostream>
#include <list>
#include <vector>
#include "vector.hpp"
#include "list.hpp"
#include <map>
#include <set>
#include "map.hpp"
#include <stack>
// #include "DequeIterator.hpp"

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
	// ft::DequeBlock<int> deque;
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

	// for (int i = 0; i < 1000; i++)
	// 	deque.push_front(i);
	// for (int i = 0; i < 1000; ++i)
	// 	deque.pop_back();
	// for (int i = 0; i < 10; ++i)
	// 	deque.push_back(i);
	// for (int i = 0; i < 20; ++i)
	// 	deque.insert(deque.begin(), i);
	// for (int i = 0; i < 20; ++i)
	// 	deque.insert(deque.end(), i);


	// std::cout << "size: " << deque.size() << std::endl;
	

	// for (ft::DequeBlock<int>::iterator it = deque.begin(); it != deque.end(); ++it)
	// 	std::cout << *it << std::endl;

	// std::cout << std::endl << deque.end() - deque.begin() << std::endl;

	int* p1 = 0x0;
	int a;
	int* p2 = &a;

	std::cout << p1 + p2 << std::endl;




}
