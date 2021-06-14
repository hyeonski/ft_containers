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

	template<typename T>
	class ListIterator
	{
		public:

			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;
			typedef const T& const_reference;
			typedef ft::bidirectional_iterator_tag iterator_category;

			ListNode<T>* ptr; // 고민해보자
			// commmon
			ListIterator(ListNode<T>* ptr = NULL) : ptr(ptr) {}
			template <typename U>
			ListIterator(ListNode<U>* ptr = NULL) : ptr((ListNode<T>*)ptr) {}
			// ListIterator(ListNode<U>* ptr = NULL) : ptr(const_cast<ft::ListNode<T>* >(ptr)) {}
			template <typename U>
			ListIterator(const ListIterator<U>& ref) : ptr((ListNode<T>*)ref.ptr) {}
			
			ListIterator<T>& operator=(const ListIterator<T>& ref)
			{
				if (this != &ref)
					this->ptr = ref.ptr;
				return (*this);
			}

			virtual ~ListIterator() {}
			
			ListIterator& operator++()
			{
				this->ptr = this->ptr->_next;
				return (*this);
			}

			ListIterator operator++(int)
			{
				ListIterator temp(*this);

				this->ptr = this->ptr->_next;
				return (temp);
			}

			// input
			template <typename U>
			bool operator==(const ListIterator<U>& iter) const
			{
				return (this->ptr == (ListNode<T>*)iter.ptr);
			}

			template <typename U>
			bool operator!=(const ListIterator<U>& iter) const
			{
				return (this->ptr != (ListNode<T>*)iter.ptr);
			}

			reference operator*()
			{
				return (this->ptr->_value);
			}

			const_reference operator*() const
			{
				return (this->ptr->_value);
			}

			pointer operator->()
			{
				return (&(this->ptr->_value));
			}

			const T* operator->() const
			{
				return (&(this->ptr->_value));
			}

			// output

			// forward

			// bidirectional
			ListIterator& operator--()
			{
				this->ptr = this->ptr->_prev;
				return (*this);
			}

			ListIterator operator--(int)
			{
				ListIterator temp(*this);

				this->ptr = this->ptr->_prev;
				return (temp);
			}
	};

	template<typename T>
	class ListReverseIterator
	{
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;
			typedef const T& const_reference;
			// typedef Category iterator_category;

			ListNode<T>* ptr; // 고민해보자

			// commmon
			ListReverseIterator(ListNode<T>* ptr = NULL) : ptr(ptr) {}
			template <typename U>
			ListReverseIterator(ListNode<U>* ptr = NULL) : ptr((ListNode<T>*)ptr) {}
			template <typename U>
			ListReverseIterator(const ListReverseIterator<U>& ref) : ptr((ListNode<T>*)ref.ptr) {}
			template <typename U>
			ListReverseIterator(const ListIterator<U>& ref) : ptr((ListNode<T>*)ref.ptr->_prev) {}

			ListReverseIterator<T>& operator=(const ListReverseIterator<T>& ref)
			{
				if (this != &ref)
					this->ptr = ref.ptr;
				return (*this);
			}

			virtual ~ListReverseIterator() {}
			
			ListReverseIterator& operator++()
			{
				this->ptr = this->ptr->_prev;
				return (*this);
			}

			ListReverseIterator operator++(int)
			{
				ListReverseIterator temp(*this);

				this->ptr = this->ptr->_prev;
				return (temp);
			}

			// input
			template <typename U>
			bool operator==(const ListReverseIterator<U>& iter) const
			{
				return (this->ptr == (ListNode<T>*)iter.ptr);
			}

			template <typename U>
			bool operator!=(const ListReverseIterator<U>& iter) const
			{
				return (this->ptr != (ListNode<T>*)iter.ptr);
			}

			reference operator*()
			{
				return (this->ptr->_value);
			}

			const_reference operator*() const
			{
				return (this->ptr->_value);
			}

			pointer operator->()
			{
				return (&(this->ptr->_value));
			}

			const T* operator->() const
			{
				return (&(this->ptr->_value));
			}

			// output

			// forward

			// bidirectional
			ListReverseIterator& operator--()
			{
				this->ptr = this->ptr->_next;
				return (*this);
			}

			ListReverseIterator operator--(int)
			{
				ListReverseIterator temp(*this);

				this->ptr = this->ptr->_next;
				return (temp);
			}

			ListIterator<T> base(void)
			{
				return (ListIterator<T>(this->ptr->_next));
			}
	};
}

#endif