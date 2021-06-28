#include <iostream>
#include <list>
#include <vector>
#include "vector.hpp"
#include "list.hpp"
#include <map>
#include <set>
#include "map.hpp"
#include <stack>
#include "deque.hpp"

class A
{
	public:
	long long a;
	long long b;
	long long c;
	long long d;
	long long arr[4];
	long long arr2[8];
	long long arr3[112];
	

	public:
		A()
		{
			// std::cout << "default" << std::endl;
		}

		A(long long n)
		{
			a = n;
		}

		A(const A& a)
		{
			this->a = a.a;
			// std::cout << "copy" << std::endl;
		}

		~A()
		{
			// std::cout << "destruct" << std::endl;
		}
};

std::ostream& operator<<(std::ostream& os, const A& a)
{
	return (os << a.a);
}

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
	ft::deque<int> deque;
	// for (int i = 0; i < 100; ++i)
	// 	deque.push_back(i);
	// deque.insert(deque.begin(), 500);
	// deque.insert(deque.end(), 500);
	// deque.insert(--(--deque.end()), 500);


	deque.push_back(1);
	deque.push_back(2);
	deque.push_back(3);
	deque.push_back(4);
	deque.push_back(5);

	deque.insert(deque.begin(), 10);
	deque.insert(++(++deque.begin()), 10);
	deque.insert(deque.end(), 10);
	deque.insert(--(--deque.end()), 10);

	deque.insert(deque.begin(), 3, 11);
	deque.insert(++deque.begin(), 3, 12);
	deque.insert(deque.end(), 3, 13);
	deque.insert(--deque.end(), 3, 14);
	deque.erase(++deque.begin(), --deque.end());



	for (ft::deque<int>::const_iterator iter = deque.begin(); iter != deque.end(); ++iter)
		std::cout << *iter << std::endl;
	std::cout << "size:" << deque.size() << std::endl;
}
