#include <iostream>
#include "list.hpp"
#include <list>
#include <vector>

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

template <typename T>
void	printReverse(NS::list<T> &lst)
{
	typename NS::list<T>::iterator it = lst.end(), ite = lst.begin();

	std::cout << "printReverse:" << std::endl;
	while (it-- != ite)
		std::cout << "-> " << *it << std::endl;
	std::cout << "_______________________________________________" << std::endl;
}

template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}

template <typename T>
T	inc(T it, int n)
{
	while (n-- > 0)
		++it;
	return (it);
}

template <typename T>
T	dec(T it, int n)
{
	while (n-- > 0)
		--it;
	return (it);
}


int main()
{
	{
		std::cout << "-------- list default constructor test --------" << std::endl;
		NS::list<int> list;
		std::cout << "is empty()?: " << list.empty() << std::endl;
		std::cout << "size: " << list.size() << std::endl;
	}

	{
		std::cout << "--------- list fill constructor-pointer test --------" << std::endl;
		int arr[] = {0, 1, 2, 3, 4};
		NS::list<int> list(arr, arr + 5);

		std::cout << "size(): " << list.size() << std::endl;
		for (NS::list<int>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
			std::cout << "value: " << *iter << std::endl;
	}

	{
		std::cout << "--------- list fill constructor-iterator test --------" << std::endl;
		std::vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(4);
		vec.push_back(5);

		std::cout << "vector size(): " << vec.size() << std::endl;
		for (std::vector<int>::const_iterator iter = vec.begin(); iter != vec.end(); ++iter)
			std::cout << "vec: " << *iter << std::endl;

		NS::list<int> list(vec.begin(), vec.end());

		std::cout << "list size(): " << list.size() << std::endl;
		for (NS::list<int>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
			std::cout << "list: " << *iter << std::endl;
	}

	{
		std::cout << "--------- list fill constructor-value test --------" << std::endl;
		NS::list<int> list(5, 100);

		// iterator로 자료 보여주기 필요
		std::cout << "size(): " << list.size() << std::endl;
		for (NS::list<int>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
			std::cout << "value: " << *iter << std::endl;
	}

	{
		std::cout << "--------- list copy constructor test --------" << std::endl;

		NS::list<int> lst(5);
		NS::list<int>::iterator it = lst.begin(), ite = lst.end();
		for (int i = 0; it != ite; ++it)
			*it = ++i;
	
		it = lst.begin();
		NS::list<int> lst_range(it, --(--ite));

		for (int i = 0; it != ite; ++it)
			*it = ++i * 5;

		it = lst.begin();
		NS::list<int> lst_copy(lst);

		for (int i = 0; it != ite; ++it)
			*it = ++i * 7;
		lst_copy.push_back(42);
		lst_copy.push_back(21);

		printSize(lst);
		printSize(lst_range);
		printSize(lst_copy);
	}

	{
		std::cout << "--------- list assignation operator test --------" << std::endl;

		NS::list<int> lst(5);
		NS::list<int>::iterator it = lst.begin(), ite = lst.end();
		for (int i = 0; it != ite; ++it)
			*it = ++i;
	
		it = lst.begin();
		NS::list<int> lst_range(it, --(--ite));

		for (int i = 0; it != ite; ++it)
			*it = ++i * 5;

		it = lst.begin();
		NS::list<int> lst_copy(lst);

		for (int i = 0; it != ite; ++it)
			*it = ++i * 7;
		lst_copy.push_back(42);
		lst_copy.push_back(21);

		std::cout << "\t-- BEFORE --" << std::endl;
		printSize(lst);
		printSize(lst_range);
		printSize(lst_copy);

		lst = lst_copy;
		lst_copy = lst_range;
		lst_range.clear();

		std::cout << "\t-- AFTER --" << std::endl;
		printSize(lst);
		printSize(lst_range);
		printSize(lst_copy);
	}


	{
		std::cout << "--------- list iterator test --------" << std::endl;
		const int size = 5;
		NS::list< foo<int> > lst(size);
		NS::list< foo<int> >::iterator it(lst.begin());
		NS::list< foo<int> >::const_iterator ite(lst.end());

		for (int i = 1; it != ite; ++i)
			*it++ = i;
		printSize(lst, 1);

		it = lst.begin();
		ite = lst.begin();

		std::cout << *(++ite) << std::endl;
		std::cout << *(ite++) << std::endl;
		std::cout << *ite++ << std::endl;
		std::cout << *++ite << std::endl;

		it->m();
		ite->m();

		std::cout << *(++it) << std::endl;
		std::cout << *(it++) << std::endl;
		std::cout << *it++ << std::endl;
		std::cout << *++it << std::endl;

		std::cout << *(--ite) << std::endl;
		std::cout << *(ite--) << std::endl;
		std::cout << *--ite << std::endl;
		std::cout << *ite-- << std::endl;

		(*it).m();
		(*ite).m();

		std::cout << *(--it) << std::endl;
		std::cout << *(it--) << std::endl;
		std::cout << *it-- << std::endl;
		std::cout << *--it << std::endl;
	}

	{
		std::cout << "--------- list iterator test - assign value to const_iterator(error expected) --------" << std::endl;
		NS::list<int> lst(2);
		NS::list<int>::const_iterator ite = lst.begin();

		// *ite = 42; // < -- error expected
	}

	{
		std::cout << "--------- list iterator test - relation between different type container(error expected) --------" << std::endl;
		NS::list<int>::iterator it;
		NS::list<float>::const_iterator ite;

		// std::cout << (it != ite) << std::endl;
	}

	{
		std::cout << "--------- list iterator test - assign iterator with const_iterator(error expected) --------" << std::endl;
		const NS::list<int> lst(5);
		// NS::list<int>::iterator it = lst.begin(); // <-- error expected

		(void)it;
	}

	{
		
	}


}
