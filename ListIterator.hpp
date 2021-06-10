#ifndef LISTITERATOR_HPP
# define LISTITERATOR_HPP

# include "enable_if.hpp"

namespace ft
{
	template < class T >
	struct ListNode
	{
		public:
			ListNode* _prev;
			ListNode* _next;
			T _value;

			ListNode() : _prev(NULL), _next(NULL){}
			ListNode(const T& value) : _prev(NULL), _next(NULL), _value(value) {}
			ListNode(const ListNode& ref)
			{
				this->_prev = ref._prev;
				this->_next = ref._next;
				this->_value = ref._value;
			}
	};

	template<typename T>
	class ListIterator
	{
		public:

			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;
			typedef Category iterator_category;

			ListNode<T>* ptr; // 고민해보자
			// commmon
			ListIterator(ListNode<T>* ptr = NULL) : ptr(ptr) {}
			// copy constructor
			ListIterator& operator=(const ListIterator& ref)
			{
				if (this != &ref)
					this->ptr = ref.ptr;
				return (*this);
			}
			// destructor
			ListIterator& operator++()
			{
				++this->ptr;
				return (*this);
			}

			ListIterator operator++(int)
			{
				ListIterator temp(*this);

				++this->ptr;
				return (temp);
			}

			// input
			template <typename U>
			bool operator==(const ListIterator<U>& iter) const
			{
				return (this->ptr == iter.ptr);
			}

			template <typename U>
			bool operator!=(const ListIterator<U>& iter) const
			{
				return (this->ptr != iter.ptr);
			}

			
			// output


			// forward


			// bidirectional

	};
}

#endif