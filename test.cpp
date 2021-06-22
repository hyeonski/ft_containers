#include <iostream>
#include <list>
#include <vector>
#include "vector.hpp"
#include "list.hpp"
#include <map>
#include <set>
#include "map.hpp"


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
	// std::list<ft::pair<int, int> > list;

	// for (int i = 1; i < 9; ++i)
	// 	list.push_back(ft::pair<int, int>(i, i));


	// ft::map<int, int> map(list.begin(), list.end());
	// // map.insert(ft::pair<int, int>(1, 1));
	// // map.insert(ft::pair<int, int>(2, 2));
	// // map.insert(ft::pair<int, int>(3, 3));


	// for (ft::map<int, int>::iterator iter = map.begin(); iter != map.end(); ++iter)
	// {
	// 	std::cout << iter->first << std::endl;
	// 	std::cout << iter->second << std::endl << std::endl;
	// }

	std::map<int, int> map1;
	std::map<int, int> map2;

	std::cout << (map1 == map2) << std::endl;

	// for (ft::map<int, int>::reverse_iterator iter = map.rbegin(); iter != map.rend(); ++iter)
	// {
	// 	std::cout << iter->first << std::endl;
	// 	std::cout << iter->second << std::endl << std::endl;
	// }
}