#ifndef LIST_HPP
# define LIST_HPP

namespace ft
{
	template < class T >
	struct list_node
	{
		public:
			list_node* _prev;
			list_node* _next;
			T _value;

			list_node() : _prev(NULL), _next(NULL){}
			list_node(const T& value) : _prev(NULL), _next(NULL), _value(value) {}
			list_node(const list_node& ref)
			{
				this->_prev = ref._prev;
				this->_next = ref._next;
				this->_value = ref._value;
			}
	};

	template < class T, class Alloc = std::allocator<T> >
	class list
	{
		private:
			list_node<T>* _first;
			list_node<T>* _last;
			size_t _size;
			Alloc _alloc;
			
			typedef typename Alloc::template rebind< list_node<T> >::other NodeAlloc;

			void deleteNode(list_node<T>* node)
			{
				// 비어있을 때 delete 처리해 말아?
				NodeAlloc nodeAlloc;

				list_node<T>* nodePrev = node->_prev;
				list_node<T>* nodeNext = node->_next;
	
				nodeAlloc.destroy(node);
				nodeAlloc.deallocate(node, 1);
				nodePrev->_next = nodeNext;
				nodeNext->_prev = nodePrev;
				--this->_size;
			}
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			// typedef list_iterator<T> iterator;
			// typedef list_iterator<T, true> const_iterator;
			// typedef ft::reverse_iterator<iterator> reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			// typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;
			explicit list(const allocator_type& alloc = allocator_type())
			{
				NodeAlloc nodeAlloc;

				this->_alloc = alloc;
				this->_first = nodeAlloc.allocate(1);
				nodeAlloc.construct(this->_first, list_node<T>());
				this->_last = _first; // end()도 더미노드?
				this->_size = 0;
			}

			explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _first(NULL), _last(NULL), _size(0)
			{
				NodeAlloc nodeAlloc;
	
				this->_alloc = alloc;
				this->_first = nodeAlloc.allocate(1);
				nodeAlloc.construct(this->_first, list_node<T>());
				this->_last = _first;

				for (size_type i = 0; i < n; i++)
					this->push_back(val);

				this->_size = n; //explicitly
			}

			// template <class InputIterator>
			// list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			// {

			// }

			// list(const list& x)
			// {

			// }
			
			// ~list()
			// {

			// }

			// list& operator=(const list& x)
			// {

			// }

			// iterator begin();
			// const_iterator begin() const;
			// iterator end();
			// const_iterator end() const;
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

			// size_type max_size() const;

			// reference front();

			// const_reference front() const;

			// reference back();

			// const_reference back() const;

			// template <class InputIterator>
			// void assign (InputIterator first, InputIterator last);

			// void assign (size_type n, const value_type& val)
			// {
				
			// }

			void push_front (const value_type& val)
			{
				NodeAlloc nodeAlloc;

				list_node<T> *newNode = nodeAlloc.allocate(1);
				nodeAlloc.construct(newNode, list_node<T>(val));
				if (this->_first == this->_last)
				{
					this->_first = newNode;
					this->_first->_prev = this->_last;
					this->_first->_next = this->_last;
					this->_last->_prev = this->_first;
					this->_last->_next = this->_first;
				}
				else
				{
					newNode->_prev = this->_last;
					newNode->_next = this->_first;
					this->_first->_prev = newNode;
					this->_first = newNode;
					this->_last->_next = newNode;
				}
				++this->_size;
			}

			void pop_front()
			{
				list_node<T>* deleteFront = this->_first;
				this->_first = this->_first->_next;
				this->deleteNode(deleteFront);
			}

			void push_back(const value_type& val)
			{
				NodeAlloc nodeAlloc;

				list_node<T> *newNode = nodeAlloc.allocate(1);
				nodeAlloc.construct(newNode, list_node<T>(val));

				if (this->_first == this->_last)
				{
					this->_first = newNode;
					this->_first->_prev = this->_last;
					this->_first->_next = this->_last;
					this->_last->_prev = this->_first;
					this->_last->_next = this->_first;
				}
				else
				{
					list_node<T> *beforeLast = this->_last->_prev;
					beforeLast->_next = newNode;
					newNode->_prev = beforeLast;
					newNode->_next = this->_last;
					this->_last->_prev = newNode;
				}
				++this->_size;
			}

			void pop_back()
			{
				list_node<T>* deleteBack = this->_last->_prev;
				this->deleteNode(deleteBack);
			}

			// iterator insert (iterator position, const value_type& val);
			
			// void insert (iterator position, size_type n, const value_type& val);
			
			// template <class InputIterator>
			// void insert (iterator position, InputIterator first, InputIterator last);
			
			// iterator erase (iterator position);
			
			// iterator erase (iterator first, iterator last);
			
			// void swap (list& x);
			
			// void resize (size_type n, value_type val = value_type());
			
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