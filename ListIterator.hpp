#ifndef LISTITERATOR_HPP
# define LISTITERATOR_HPP

# include "iterator.hpp"
# include "utils.hpp"

namespace ft
{
	template < class T >
	struct ListNode
	{
		public:
			ListNode* _prev;
			ListNode* _next;
			T _value;

			ListNode() : _prev(NULL), _next(NULL), _value() {}
			ListNode(const T& value) : _prev(NULL), _next(NULL), _value(value) {}
			ListNode(const ListNode& ref) : _prev(ref._prev), _next(ref._next), _value(ref._value) {}
	};

	template<typename T, bool IsConst>
	class ListIterator
	{
		private:
			typedef typename choose<IsConst, const ListNode<T>*, ListNode<T>* >::type Node;

		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;
			typedef const T& const_reference;
			typedef ft::bidirectional_iterator_tag iterator_category;

			Node* _ptr;

			// commmon
			ListIterator(ListNode<T>* ptr = NULL) : _ptr(ptr) {}
			// template <typename U>
			// ListIterator(ListNode<U>* ptr = NULL) : _ptr(const_cast<ListNode<T>*>(ptr)) {}
			ListIterator(const ListIterator<T, false>& ref) : _ptr(ref._ptr) {}
			
			ListIterator& operator=(const ListIterator& ref)
			{
				if (this != &ref)
					this->_ptr = ref._ptr;
				return (*this);
			}

			virtual ~ListIterator() {}
			
			ListIterator& operator++()
			{
				this->_ptr = this->_ptr->_next;
				return (*this);
			}

			ListIterator operator++(int)
			{
				ListIterator temp(*this);

				this->_ptr = this->_ptr->_next;
				return (temp);
			}

			// input
			bool operator==(const ListIterator<T, true>& iter) const
			{
				return (this->_ptr == iter._ptr);
			}

			bool operator==(const ListIterator<T, false>& iter) const
			{
				return (this->_ptr == iter._ptr);
			}

			bool operator!=(const ListIterator<T, true>& iter) const
			{
				return (this->_ptr != iter._ptr);
			}

			bool operator!=(const ListIterator<T, false>& iter) const
			{
				return (this->_ptr != iter._ptr);
			}

			const_reference operator*() const
			{
				return (this->_ptr->_value);
			}

			reference operator*()
			{
				return (this->_ptr->_value);
			}

			const T* operator->() const
			{
				return (&(this->_ptr->_value));
			}

			pointer operator->()
			{
				return (&(this->_ptr->_value));
			}

			// output

			// forward

			// bidirectional
			ListIterator& operator--()
			{
				this->_ptr = this->_ptr->_prev;
				return (*this);
			}

			ListIterator operator--(int)
			{
				ListIterator temp(*this);

				this->_ptr = this->_ptr->_prev;
				return (temp);
			}
	};

}

#endif