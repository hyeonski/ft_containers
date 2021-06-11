#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include "enable_if.hpp"
# include "ListIterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class list
	{
		private:
			ListNode<T>* _first;
			ListNode<T>* _last;
			size_t _size;
			Alloc _alloc;
			
			typedef typename Alloc::template rebind< ListNode<T> >::other NodeAlloc; 

			void addNodeFront(ListNode<T>* pos, const T& val)
			{
				ListNode<T>* prevNode = pos->_prev;
				ListNode<T>* nextNode = pos;

				NodeAlloc nodeAlloc;
				ListNode<T>* newNode = nodeAlloc.allocate(1);
				nodeAlloc.construct(newNode, ListNode<T>());
				newNode->_value = val;

				if (pos == this->_first)
					this->_first = newNode;
				prevNode->_next = newNode;
				nextNode->_prev = newNode;
				newNode->_prev = prevNode;
				newNode->_next = nextNode;
				++this->_size;
			}

			void deleteNode(ListNode<T>* node)
			{
				// 비어있을 때 delete 처리해 말아?
				NodeAlloc nodeAlloc;

				ListNode<T>* nodePrev = node->_prev;
				ListNode<T>* nodeNext = node->_next;

				if (node == this->_first)
					this->_first = this->_first->_next;
				nodeAlloc.destroy(node);
				nodeAlloc.deallocate(node, 1);
				nodePrev->_next = nodeNext;
				nodeNext->_prev = nodePrev;
				--this->_size;
				if (this->_size == 0)
					this->_first = _last;
			}
			void allocateBaseNode()
			{
				NodeAlloc nodeAlloc;

				this->_first = nodeAlloc.allocate(1);
				nodeAlloc.construct(this->_first, ListNode<T>());
				this->_last = _first;
				this->_last->_prev = this->_first;
				this->_last->_next = this->_first;
			}
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef ListIterator<T> iterator;
			typedef ListIterator<const T> const_iterator;
			// typedef ft::reverse_iterator<iterator> reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			// typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;
			explicit list(const allocator_type& alloc = allocator_type())
			{
				this->_alloc = alloc;

				this->allocateBaseNode();

				this->_size = 0;
			}

			explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _first(NULL), _last(NULL), _size(0)
			{
				this->_alloc = alloc;

				this->allocateBaseNode();

				for (size_type i = 0; i < n; i++)
					this->push_back(val);

				this->_size = n; //explicitly
			}

			template <class InputIterator>
			list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = NULL) : _first(NULL), _last(NULL), _size(0)
			{
				this->_alloc = alloc;

				this->allocateBaseNode();

				for (InputIterator iter = first; iter != last; iter++)
					this->push_back(*iter);
			}

			list(const list& x)
			{
				this->_alloc = x._alloc;
				this->allocateBaseNode();
				this->_size = 0;
				*this = x;
			}
			
			~list()
			{
				this->clear();
				
				NodeAlloc nodeAlloc;
				nodeAlloc.destroy(this->_first);
				nodeAlloc.deallocate(this->_first, 1);
			}

			list& operator=(const list& x)
			{
				if (this != &x)
					assign(x.begin(), x.end());
				return (*this);
			}

			iterator begin()
			{
				return (iterator(this->_first));
			}

			const_iterator begin() const
			{
				return (const_iterator(this->_first));
			}
			
			iterator end()
			{
				return (iterator(this->_last));
			}
			
			const_iterator end() const
			{
				return (const_iterator(this->_last));
			}

			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;
			// reverse_iterator rend();
			// const_reverse_iterator rend() const;

			bool empty() const
			{
				return (this->_size == 0);
			}

			size_type size() const
			{
				return (this->_size);
			}

			size_type max_size() const
			{
				return (NodeAlloc().max_size());
			}

			reference front()
			{
				return (this->_first->_value);
			}

			const_reference front() const
			{
				return (this->_first->_value);
			}

			reference back()
			{
				return (this->_last->_prev->_value);
			}

			const_reference back() const
			{
				return (this->_last->_prev->_value);
			}

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = NULL)
			{
				this->clear();

				for (InputIterator iter = first; iter != last; iter++)
					this->push_back(*iter);
			}

			void assign (size_type n, const value_type& val)
			{
				this->clear();

				for (size_type i = 0; i < n; i++)
					this->push_back(val);

				this->_size = n; //explicitly
			}

			void push_front (const value_type& val)
			{
				this->addNodeFront(this->_first, val);
			}

			void pop_front()
			{
				this->deleteNode(this->_first);
			}

			void push_back(const value_type& val)
			{
				this->addNodeFront(this->_last, val);
			}

			void pop_back()
			{
				ListNode<T>* deleteBack = this->_last->_prev;
				this->deleteNode(deleteBack);
			}

			iterator insert (iterator position, const value_type& val)
			{
				this->addNodeFront(position.ptr, val);
				return (--position);
			}
			
			void insert (iterator position, size_type n, const value_type& val)
			{
				for (size_type i = 0; i < n; ++i)
					this->addNodeFront(position.ptr, val);
			}
			
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = NULL)
			{
				for (InputIterator iter = first; iter != last; iter++)
					this->addNodeFront(position.ptr, *iter);
			}

			iterator erase (iterator position)
			{
				iterator temp = position++;
				this->deleteNode(temp.ptr);
				return (position);
			}
			
			iterator erase (iterator first, iterator last)
			{
				iterator temp;

				for (iterator iter = first; iter != last; )
				{
					temp = iter++;
					this->deleteNode(temp.ptr);
				}
				return (last);
			}

			void swap (list& x)
			{
				ListNode<T>* temp = x._last;
				x._last = this->_last;
				this->_last = temp;

				x._first = x._last->_next;
				this->_first = this->_last->_next;

				size_type size_temp = x._size;
				x._size = this->_size;
				this->_size = size_temp;
			}
			
			void resize (size_type n, value_type val = value_type())
			{
				size_type differ;
				if (n > this->_size)
				{
					differ = n - this->_size;
					for (size_type i = 0; i < differ; ++i)
						this->push_back(val);
				}
				else
				{
					differ = this->_size - n;
					for (size_type i = 0; i < differ; ++i)
						this->pop_back();
				}
			}
			
			void clear()
			{
				while (this->_size > 0)
					this->pop_back();
			}

			// void splice (iterator position, list& x);
			
			// void splice (iterator position, list& x, iterator i);
			
			// void splice (iterator position, list& x, iterator first, iterator last);
			
			// void remove (const value_type& val);
			
			// template <class Predicate>
			// void remove_if (Predicate pred);
			
			// void unique();
			
			// template <class BinaryPredicate>
			// void unique (BinaryPredicate binary_pred);
			
			// void merge (list& x);
			
			// template <class Compare>
			// void merge (list& x, Compare comp);
			
			// void sort();
			
			// template <class Compare>
			// void sort (Compare comp);
			
			// void reverse();

	};
}

// template <class T, class Alloc>
//   bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
// template <class T, class Alloc>
//   bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
// template <class T, class Alloc>
//   bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
// template <class T, class Alloc>
//   bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
// template <class T, class Alloc>
//   bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
// template <class T, class Alloc>
//   bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

// template <class T, class Alloc>
//   void swap (list<T,Alloc>& x, list<T,Alloc>& y);


#endif