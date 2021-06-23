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
	ft::map<int, int> map;
	map[7] = 7;
	map[3] = 3;
	map[11] = 11;
	map[1] = 1;
	map[5] = 5;
	map[9] = 9;
	map[13] = 13;

	std::cout << map.lower_bound(0)->first << std::endl;
	std::cout << map.lower_bound(1)->first << std::endl;
	std::cout << map.lower_bound(2)->first << std::endl;
	std::cout << map.lower_bound(3)->first << std::endl;
	std::cout << map.lower_bound(4)->first << std::endl;
	std::cout << map.lower_bound(5)->first << std::endl;
	std::cout << map.lower_bound(6)->first << std::endl;
	std::cout << map.lower_bound(7)->first << std::endl;
	std::cout << map.lower_bound(8)->first << std::endl;
	std::cout << map.lower_bound(9)->first << std::endl;
	std::cout << map.lower_bound(10)->first << std::endl;
	std::cout << map.lower_bound(11)->first << std::endl;
	std::cout << map.lower_bound(12)->first << std::endl;
	std::cout << map.lower_bound(13)->first << std::endl;
	std::cout << map.lower_bound(14)->first << std::endl;
	std::cout << std::endl;

	std::cout << map.upper_bound(0)->first << std::endl;
	std::cout << map.upper_bound(1)->first << std::endl;
	std::cout << map.upper_bound(2)->first << std::endl;
	std::cout << map.upper_bound(3)->first << std::endl;
	std::cout << map.upper_bound(4)->first << std::endl;
	std::cout << map.upper_bound(5)->first << std::endl;
	std::cout << map.upper_bound(6)->first << std::endl;
	std::cout << map.upper_bound(7)->first << std::endl;
	std::cout << map.upper_bound(8)->first << std::endl;
	std::cout << map.upper_bound(9)->first << std::endl;
	std::cout << map.upper_bound(10)->first << std::endl;
	std::cout << map.upper_bound(11)->first << std::endl;
	std::cout << map.upper_bound(12)->first << std::endl;
	std::cout << map.upper_bound(13)->first << std::endl;
	std::cout << map.upper_bound(14)->first << std::endl;
}
