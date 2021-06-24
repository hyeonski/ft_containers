#include <iostream>
#include <list>
#include <vector>
#include "vector.hpp"
#include "list.hpp"
#include <map>
#include <set>
#include "map.hpp"
#include <stack>

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
	func();
	std::set<int> set;
	set.insert(1);

	std::set<int>::const_iterator iter = set.begin();
	set.erase(iter);
	
}
