#include <iostream>
#include "list.hpp"
#include <list>
#include <vector>
#include <cmath>

#ifndef NS
# define NS ft
#endif

template <typename T>
void	printSize(NS::list<T> const &lst, bool print_content = 1)
{
	std::cout << "size: " << lst.size() << std::endl;
	std::cout << "max_size: " << lst.max_size() << std::endl;
	if (print_content)
	{
		typename NS::list<T>::const_iterator it = lst.begin(), ite = lst.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}
