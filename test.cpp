#include <iostream>
#include <list>
#include <vector>
#include "vector.hpp"
#include "list.hpp"
#include <map>
#include <set>
// #include "RBTree.hpp"
#include "utils.hpp"


template <typename T>
class A
{

	public:
		T value;
		A() : value(0) {}
		void foo(A<const T>& ref)
		{
			std::cout << "ASDf" << std::endl;
		}
};

class Test
{
	public:
		Test()
		{
			std::cout << "default" << std::endl;
		}
		Test(const Test& test)
		{
			std::cout << "copy" << std::endl;
		}
		~Test()
		{
			std::cout << "destruct" << std::endl;
		}
};

template <typename Key, typename Value>
class value_compare
{
	typedef ft::less<Key> Compare;
	protected:
		Compare comp;
		value_compare (Compare c) : comp(c) {}
	
	public:
		value_compare () : comp(Compare()) {}
		typedef bool	result_type;
		typedef ft::pair<Key, Value>	first_argument_type;
		typedef ft::pair<Key, Value>	second_argument_type;
		bool operator() (const first_argument_type& x, const second_argument_type& y) const
		{
			return comp(x.first, y.first);
		}
};

class temp_compare
{	
	public:
		typedef bool	result_type;
		typedef int	first_argument_type;
		typedef int	second_argument_type;
		bool operator() (const first_argument_type& x, const second_argument_type& y) const
		{
			return (x < y);
		}
};

int main()
{
	std::multimap<int, int> map;

	map.insert(std::pair<int, int>(1, 2));
	map.insert(std::pair<int, int>(1, 1));
	map.insert(std::pair<int, int>(1, 3));
	map.insert(std::pair<int, int>(1, 4));

	std::multimap<int, int>::iterator iter = map.find(1);
	std::cout << (*iter).second << std::endl;
	iter = map.find(1);
	std::cout << (*iter).second << std::endl;

	// std::cout << iter->second << std::endl;
	// iter--;
	// std::cout << iter->second << std::endl;
	// iter--;
	// std::cout << iter->second << std::endl;
	// iter--;
	// std::cout << iter->second << std::endl;
	// iter--;
	// std::cout << iter->second << std::endl;
	// iter++;
	// std::cout << iter->second << std::endl;
	// iter++;
	// std::cout << iter->second << std::endl;
	// iter++;



	// ft::RBTree<ft::pair<int, int>, value_compare<int, int> > tree;
	// tree.insert(ft::pair<int, int>(1, 10));
	// tree.insert(ft::pair<int, int>(1, 11));
	// tree.insert(ft::pair<int, int>(1, 12));
	// tree.insert(ft::pair<int, int>(1, 13));
	// tree.insert(ft::pair<int, int>(1, 14));
	// tree.insert(ft::pair<int, int>(1, 15));
	// ft::RBTree<ft::pair<int, int>, value_compare<int, int> >::TreeNode* node = tree.find(ft::pair<int, int>(1, 0));
	// std::cout << node->_value.second << std::endl;
	// node = tree.getNextNode(node);
	// std::cout << node->_value.second << std::endl;
	// node = tree.getNextNode(node);
	// std::cout << node->_value.second << std::endl;
	// node = tree.getNextNode(node);
	// std::cout << node->_value.second << std::endl;
	// node = tree.getNextNode(node);
	// std::cout << node->_value.second << std::endl;


	// node = tree.getNextNode(node);
	// std::cout << node->_value.second << std::endl;
	// node = tree.getNextNode(node);
	// std::cout << node->_value.second << std::endl;
	// node = tree.getNextNode(node);
	// std::cout << node->_value.second << std::endl;



	// ft::RBTree<int, temp_compare> tree;
	// tree.insert(1);
	// tree.insert(2);
	// tree.insert(3);
	// tree.insert(4);
	// tree.insert(5);

	// ft::RBTree<int, temp_compare>::TreeNode* node = tree.find(3);
	// std::cout << node->_value << std::endl;

}