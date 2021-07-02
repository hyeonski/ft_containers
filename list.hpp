#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include "utils.hpp"
# include "ListIterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class list
	{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef ft::ListIterator<T, false> iterator;
			typedef ft::ListIterator<T, true> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;

		private:
			ListNode<T>* _base;
			size_t _size;
			Alloc _alloc;
			
			typedef typename Alloc::template rebind< ListNode<T> >::other NodeAlloc; 

			void addNodeFront(ListNode<T>* pos, const T& val)
			{
				ListNode<T>* prevNode = pos->_prev;
				ListNode<T>* nextNode = pos;

				NodeAlloc nodeAlloc;
				ListNode<T>* newNode = nodeAlloc.allocate(1);
				nodeAlloc.construct(newNode, ListNode<T>(val));

				prevNode->_next = newNode;
				nextNode->_prev = newNode;
				newNode->_prev = prevNode;
				newNode->_next = nextNode;
				++this->_size;
			}

			void deleteNode(ListNode<T>* node)
			{
				NodeAlloc nodeAlloc;

				ListNode<T>* nodePrev = node->_prev;
				ListNode<T>* nodeNext = node->_next;

				nodeAlloc.destroy(node);
				nodeAlloc.deallocate(node, 1);
				nodePrev->_next = nodeNext;
				nodeNext->_prev = nodePrev;
				--this->_size;
			}

			void allocateBaseNode()
			{
				NodeAlloc nodeAlloc;

				this->_base = nodeAlloc.allocate(1);
				nodeAlloc.construct(this->_base, ListNode<T>());
				this->_base->_prev = this->_base;
				this->_base->_next = this->_base;
			}

			void swapNextNode(ListNode<T>* node)
			{
				if (node->_next == NULL)
					return ;
				ListNode<T>* node_next = node->_next;
				ListNode<T>* node_next_next = node_next->_next;
				ListNode<T>* node_prev = node->_prev;
				
				if (node_prev != NULL)
					node_prev->_next = node_next;
				if (node_next_next != NULL)
					node_next_next->_prev = node;
				
				node->_prev = node_next;
				node->_next = node_next_next;

				node_next->_prev = node_prev;
				node_next->_next = node;
			}


			void swapNode(ListNode<T> *a, ListNode<T> *b)
			{
				if (a == b)
					return ;
				ListNode<T>* a_prev = a->_prev;
				ListNode<T>* a_next = a->_next;
				ListNode<T>* b_prev = b->_prev;
				ListNode<T>* b_next = b->_next;

				ListNode<T>* temp_a_prev = a_prev;
				ListNode<T>* temp_a_next = a_next;
				ListNode<T>* temp_a = a;

				a->_prev = b_prev;
				a->_next = b_next;
				a_prev->_next = b;
				a_next->_prev = b;

				b->_prev = temp_a_prev;
				b->_next = temp_a_next;
				b_prev->_next = temp_a;
				b_next->_prev = temp_a;
			}

			void changePrevNext(ListNode<T>* node)
			{
				if (node != this->_base)
					this->changePrevNext(node->_next);
				ListNode<T>* temp = node->_prev;
				node->_prev = node->_next;
				node->_next = temp;
			}

		public:
			explicit list(const allocator_type& alloc = allocator_type())
			{
				this->_alloc = alloc;

				this->allocateBaseNode();

				this->_size = 0;
			}

			explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _base(NULL), _size(0)
			{
				this->_alloc = alloc;

				this->allocateBaseNode();

				for (size_type i = 0; i < n; ++i)
					this->push_back(val);

				this->_size = n; //explicitly
			}

			template <class InputIterator>
			list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = NULL) : _base(NULL), _size(0)
			{
				this->_alloc = alloc;

				this->allocateBaseNode();

				for (InputIterator iter = first; iter != last; ++iter)
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
				nodeAlloc.destroy(this->_base);
				nodeAlloc.deallocate(this->_base, 1);
			}

			list& operator=(const list& x)
			{
				if (this != &x)
					assign(x.begin(), x.end());
				return (*this);
			}

			iterator begin()
			{
				return (iterator(this->_base->_next));
			}

			const_iterator begin() const
			{
				return (const_iterator(this->_base->_next));
			}
			
			iterator end()
			{
				return (iterator(this->_base));
			}
			
			const_iterator end() const
			{
				return (const_iterator(this->_base));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(iterator(this->_base)));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(const_iterator(this->_base)));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(iterator(this->_base->_next)));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(const_iterator(this->_base->_next)));
			}

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
				return (this->_base->_next->_value);
			}

			const_reference front() const
			{
				return (this->_base->_next->_value);
			}

			reference back()
			{
				return (this->_base->_prev->_value);
			}

			const_reference back() const
			{
				return (this->_base->_prev->_value);
			}

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = NULL)
			{
				this->clear();

				for (InputIterator iter = first; iter != last; ++iter)
					this->push_back(*iter);
			}

			void assign (size_type n, const value_type& val)
			{
				this->clear();

				for (size_type i = 0; i < n; ++i)
					this->push_back(val);

				this->_size = n; //explicitly
			}

			void push_front (const value_type& val)
			{
				this->addNodeFront(this->_base->_next, val);
			}

			void pop_front()
			{
				this->deleteNode(this->_base->_next);
			}

			void push_back(const value_type& val)
			{
				this->addNodeFront(this->_base, val);
			}

			void pop_back()
			{
				this->deleteNode(this->_base->_prev);
			}

			iterator insert (iterator position, const value_type& val)
			{
				this->addNodeFront(position._ptr, val);
				return (--position);
			}
			
			void insert (iterator position, size_type n, const value_type& val)
			{
				for (size_type i = 0; i < n; ++i)
					this->addNodeFront(position._ptr, val);
			}
			
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = NULL)
			{
				for (InputIterator iter = first; iter != last; ++iter)
					this->addNodeFront(position._ptr, *iter);
			}

			iterator erase (iterator position)
			{
				iterator temp = position++;
				this->deleteNode(temp._ptr);
				return (position);
			}
			
			iterator erase (iterator first, iterator last)
			{
				iterator temp;

				for (iterator iter = first; iter != last; )
				{
					temp = iter++;
					this->deleteNode(temp._ptr);
				}
				return (last);
			}

			void swap (list& x)
			{
				ListNode<T>* temp = x._base;
				x._base = this->_base;
				this->_base = temp;

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

			void splice (iterator position, list& x)
			{
				this->splice(position, x, x.begin(), x.end());
			}
			
			void splice (iterator position, list& x, iterator i)
			{
				i._ptr->_prev->_next = i._ptr->_next;
				i._ptr->_next->_prev = i._ptr->_prev;

				i._ptr->_prev = position._ptr->_prev;
				i._ptr->_next = position._ptr;
				position._ptr->_prev->_next = i._ptr;
				position._ptr->_prev = i._ptr;

				++this->_size;
				--x._size;
			}
			
			void splice (iterator position, list& x, iterator first, iterator last)
			{
				iterator temp;

				for (iterator iter = first; iter != last; )
				{
					temp = iter;
					++iter;
					this->splice(position, x, temp);
				}
			}

			void remove (const value_type& val)
			{
				iterator temp;

				for (iterator iter = this->begin(); iter != this->end(); )
				{
					temp = iter;
					++iter;
					if (*temp == val)
						this->erase(temp);
				}
			}
			
			template <class Predicate>
			void remove_if (Predicate pred)
			{
				iterator temp;

				for (iterator iter = this->begin(); iter != this->end(); )
				{
					temp = iter;
					++iter;
					if (pred(*temp))
						this->erase(temp);
				}
			}
			
			void unique()
			{
				ListNode<T>* first = this->_base->_next;
				ListNode<T>* node;

				while (first != this->_base)
				{
					node = first->_next;
					if (node != this->_base && (first->_value == node->_value))
					{
						node = node->_next;
						this->deleteNode(first->_next);
						continue ;
					}
					first = first->_next;
				}
			}
			
			template <class BinaryPredicate>
			void unique (BinaryPredicate binary_pred)
			{
				ListNode<T>* first = this->_base->_next;
				ListNode<T>* node;

				while (first != this->_base)
				{
					node = first->_next;
					if (node != this->_base && binary_pred(first->_value, node->_value))
					{
						node = node->_next;
						this->deleteNode(first->_next);
						continue ;
					}
					first = first->_next;
				}
			}
			
			void merge (list& x)
			{
				if (&x == this)
					return ;
				iterator iter = this->begin();
				iterator x_iter = x.begin();
				iterator temp;

				while (x_iter != x.end() && iter != this->end())
				{
					if (*x_iter < *iter)
					{
						temp = x_iter++;
						this->splice(iter, x, temp);
					}
					else
						++iter;
				}
				this->splice(this->end(), x);
			}

			template <class Compare>	
			void merge (list& x, Compare comp)
			{
				if (&x == this)
					return ;
				iterator iter = this->begin();
				iterator x_iter = x.begin();
				iterator temp;

				while (x_iter != x.end() && iter != this->end())
				{
					if (comp(*x_iter, *iter))
					{
						temp = x_iter++;
						this->splice(iter, x, temp);
					}
					else
						++iter;
				}
				this->splice(this->end(), x);
			}
			
			void sort()
			{
				ListNode<T>* temp = this->_base->_next;
				while (temp->_next != this->_base)
				{
					if (temp->_value > temp->_next->_value)
					{
						this->swapNextNode(temp);
						temp = this->_base->_next;
					}
					else
						temp = temp->_next;
				}
			}

			template <class Compare>
			void sort (Compare comp)
			{
				ListNode<T>* temp = this->_base->_next;
				while (temp->_next != this->_base)
				{
					if (comp(temp->_next->_value, temp->_value))
					{
						this->swapNextNode(temp);
						temp = this->_base->_next;
					}
					else
						temp = temp->_next;
				}
			}

			void reverse()
			{
				this->changePrevNext(this->_base->_next);
			}

			allocator_type get_allocator() const
			{
				return (this->_alloc);
			}
	};

	template <class T, class Alloc>
	bool operator== (const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));	
	}

	template <class T, class Alloc>
	bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return ((lhs == rhs) || (lhs < rhs));
	}

	template <class T, class Alloc>
	bool operator> (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return (!(lhs <= rhs));
	}

	template <class T, class Alloc>
	bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
	{
		return ((lhs == rhs) || (lhs > rhs));
	}

	template <class T, class Alloc>
	void swap (list<T,Alloc>& x, list<T,Alloc>& y)
	{
		x.swap(y);
	}

}

#endif