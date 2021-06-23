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

int main()
{
	std::stack<int> stack1;
	std::stack<int> stack2;
	stack2.push(1);
	stack2.push(2);
	stack2.push(3);
	stack2.push(4);

	stack1 = stack2;
	std::stack<int> stack3(stack2);
	std::cout << stack3.top() << std::endl;
}