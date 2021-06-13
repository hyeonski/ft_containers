#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "utils.hpp"
# include "VectorIterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		private:
			T* arr;
			size_t _size;
			size_t _capacity;
			Alloc _alloc;

		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef ft::VectorIterator<T> iterator;
			typedef ft::VectorIterator<const T> const_iterator;
			typedef ft::VectorReverseIterator<T> reverse_iterator;
			typedef ft::VectorReverseIterator<const T> const_reverse_iterator;
			// typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;
			explicit vector(const allocator_type& alloc = allocator_type()) : _arr(NULL), _size(0), _capacity(0), _alloc(alloc) {}
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _arr(NULL), _size(0), _capacity(0), _alloc(alloc)
			{
				assign(n, val);
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			{
				assign(first, last);
			}

			vector (const vector& x)
			{
				assign(x.begin(), x.end());
			}



			// virtual ~vector()
			// {
			// 	if (this->arr_capacity > 0)
			// 	{
			// 		this->clear();
			// 		this->alloc.deallocate(this->arr, this->arr_capacity);
			// 	}
			// }

			// vector& operator= (const vector& x);

			// iterator begin();

			// const_iterator begin() const;

			// iterator end();

			// const_iterator end() const;

			// reverse_iterator rbegin();

			// const_reverse_iterator rbegin() const;

			// reverse_iterator rend();

			// const_reverse_iterator rend() const;

			// size_type size() const;

			// size_type max_size() const;

			// void resize (size_type n, value_type val = value_type());

			// size_type capacity() const;

			// bool empty() const;

			// void reserve (size_type n);

			// reference operator[] (size_type n);

			// const_reference operator[] (size_type n) const;

			// reference at (size_type n);

			// const_reference at (size_type n) const;

			// reference front();

			// const_reference front() const;

			// reference back();

			// const_reference back() const;

			// template <class InputIterator>
			// void assign (InputIterator first, InputIterator last);

			// void assign (size_type n, const value_type& val);

			// void push_back (const value_type& val);

			// void pop_back();

			// iterator insert (iterator position, const value_type& val);

			// void insert (iterator position, size_type n, const value_type& val);

			// template <class InputIterator>
			// void insert (iterator position, InputIterator first, InputIterator last);

			// iterator erase (iterator position);

			// iterator erase (iterator first, iterator last);

			// void swap (vector& x);

			// void clear();

			// allocator_type get_allocator() const;






			// list& operator=(const list& x)
			// {
			// 	if (this != &x)
			// 		assign(x.begin(), x.end());
			// 	return (*this);
			// }

			// iterator begin()
			// {
			// 	return (iterator(this->_base->_next));
			// }

			// const_iterator begin() const
			// {
			// 	return (const_iterator(this->_base->_next));
			// }
			
			// iterator end()
			// {
			// 	return (iterator(this->_base));
			// }
			
			// const_iterator end() const
			// {
			// 	return (const_iterator(this->_base));
			// }

			// reverse_iterator rbegin()
			// {
			// 	return (reverse_iterator(this->_base->_prev));
			// }

			// const_reverse_iterator rbegin() const
			// {
			// 	return (const_reverse_iterator(this->_base->_prev));
			// }

			// reverse_iterator rend()
			// {
			// 	return (reverse_iterator(this->_base));
			// }

			// const_reverse_iterator rend() const
			// {
			// 	return (const_reverse_iterator(this->_base));
			// }

			// bool empty() const
			// {
			// 	return (this->_size == 0);
			// }

			// size_type size() const
			// {
			// 	return (this->_size);
			// }

			// size_type max_size() const
			// {
			// 	return (NodeAlloc().max_size());
			// }

			// reference front()
			// {
			// 	return (this->_base->_next->_value);
			// }

			// const_reference front() const
			// {
			// 	return (this->_base->_next->_value);
			// }

			// reference back()
			// {
			// 	return (this->_base->_prev->_value);
			// }

			// const_reference back() const
			// {
			// 	return (this->_base->_prev->_value);
			// }

			// template <class InputIterator>
			// void assign (InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = NULL)
			// {
			// 	this->clear();

			// 	for (InputIterator iter = first; iter != last; iter++)
			// 		this->push_back(*iter);
			// }

			// void assign (size_type n, const value_type& val)
			// {
			// 	this->clear();

			// 	for (size_type i = 0; i < n; i++)
			// 		this->push_back(val);

			// 	this->_size = n; //explicitly
			// }

			// void push_front (const value_type& val)
			// {
			// 	this->addNodeFront(this->_base->_next, val);
			// }

			// void pop_front()
			// {
			// 	this->deleteNode(this->_base->_next);
			// }

			// void push_back(const value_type& val)
			// {
			// 	this->addNodeFront(this->_base, val);
			// }

			// void pop_back()
			// {
			// 	this->deleteNode(this->_base->_prev);
			// }

			// iterator insert (iterator position, const value_type& val)
			// {
			// 	this->addNodeFront(position.ptr, val);
			// 	return (--position);
			// }
			
			// void insert (iterator position, size_type n, const value_type& val)
			// {
			// 	for (size_type i = 0; i < n; ++i)
			// 		this->addNodeFront(position.ptr, val);
			// }
			
			// template <class InputIterator>
			// void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = NULL)
			// {
			// 	for (InputIterator iter = first; iter != last; iter++)
			// 		this->addNodeFront(position.ptr, *iter);
			// }

			// iterator erase (iterator position)
			// {
			// 	iterator temp = position++;
			// 	this->deleteNode(temp.ptr);
			// 	return (position);
			// }
			
			// iterator erase (iterator first, iterator last)
			// {
			// 	iterator temp;

			// 	for (iterator iter = first; iter != last; )
			// 	{
			// 		temp = iter++;
			// 		this->deleteNode(temp.ptr);
			// 	}
			// 	return (last);
			// }

			// void swap (list& x)
			// {
			// 	ListNode<T>* temp = x._base;
			// 	x._base = this->_base;
			// 	this->_base = temp;

			// 	size_type size_temp = x._size;
			// 	x._size = this->_size;
			// 	this->_size = size_temp;
			// }
			
			// void resize (size_type n, value_type val = value_type())
			// {
			// 	size_type differ;
			// 	if (n > this->_size)
			// 	{
			// 		differ = n - this->_size;
			// 		for (size_type i = 0; i < differ; ++i)
			// 			this->push_back(val);
			// 	}
			// 	else
			// 	{
			// 		differ = this->_size - n;
			// 		for (size_type i = 0; i < differ; ++i)
			// 			this->pop_back();
			// 	}
			// }
			
			// void clear()
			// {
			// 	while (this->_size > 0)
			// 		this->pop_back();
			// }

			// void splice (iterator position, list& x)
			// {
			// 	this->splice(position, x, x.begin(), x.end());
			// }
			
			// void splice (iterator position, list& x, iterator i)
			// {
			// 	i.ptr->_prev->_next = i.ptr->_next;
			// 	i.ptr->_next->_prev = i.ptr->_prev;

			// 	i.ptr->_prev = position.ptr->_prev;
			// 	i.ptr->_next = position.ptr;
			// 	position.ptr->_prev->_next = i.ptr;
			// 	position.ptr->_prev = i.ptr;

			// 	++this->_size;
			// 	--x._size;
			// }
			
			// void splice (iterator position, list& x, iterator first, iterator last)
			// {
			// 	iterator temp;

			// 	for (iterator iter = first; iter != last; )
			// 	{
			// 		temp = iter;
			// 		iter++;
			// 		this->splice(position, x, temp);
			// 	}
			// }

			// void remove (const value_type& val)
			// {
			// 	iterator temp;

			// 	for (iterator iter = this->begin(); iter != this->end(); )
			// 	{
			// 		temp = iter;
			// 		iter++;
			// 		if (*temp == val)
			// 			this->erase(temp);
			// 	}
			// }
			
			// template <class Predicate>
			// void remove_if (Predicate pred)
			// {
			// 	iterator temp;

			// 	for (iterator iter = this->begin(); iter != this->end(); )
			// 	{
			// 		temp = iter;
			// 		iter++;
			// 		if (pred(*temp))
			// 			this->erase(temp);
			// 	}
			// }
			
			// void unique()
			// {
			// 	ListNode<T>* first = this->_base->_next;
			// 	ListNode<T>* node;

			// 	while (first != this->_base)
			// 	{
			// 		node = first->_next;
			// 		if (node != this->_base && (first->_value == node->_value))
			// 		{
			// 			node = node->_next;
			// 			this->deleteNode(first->_next);
			// 			continue ;
			// 		}
			// 		first = first->_next;
			// 	}
			// }
			
			// template <class BinaryPredicate>
			// void unique (BinaryPredicate binary_pred)
			// {
			// 	ListNode<T>* first = this->_base->_next;
			// 	ListNode<T>* node;

			// 	while (first != this->_base)
			// 	{
			// 		node = first->_next;
			// 		if (node != this->_base && binary_pred(first->_value, node->_value))
			// 		{
			// 			node = node->_next;
			// 			this->deleteNode(first->_next);
			// 			continue ;
			// 		}
			// 		first = first->_next;
			// 	}
			// }
			
			// void merge (list& x)
			// {
			// 	if (&x == this)
			// 		return ;
			// 	iterator iter = this->begin();
			// 	iterator x_iter = x.begin();
			// 	iterator temp;

			// 	while (x_iter != x.end() && iter != this->end())
			// 	{
			// 		if (*x_iter < *iter)
			// 		{
			// 			temp = x_iter++;
			// 			this->splice(iter, x, temp);
			// 		}
			// 		else
			// 			iter++;
			// 	}
			// 	this->splice(this->end(), x);
			// }

			// template <class Compare>	
			// void merge (list& x, Compare comp)
			// {
			// 	if (&x == this)
			// 		return ;
			// 	iterator iter = this->begin();
			// 	iterator x_iter = x.begin();
			// 	iterator temp;

			// 	while (x_iter != x.end() && iter != this->end())
			// 	{
			// 		if (comp(*x_iter, *iter))
			// 		{
			// 			temp = x_iter++;
			// 			this->splice(iter, x, temp);
			// 		}
			// 		else
			// 			iter++;
			// 	}
			// 	this->splice(this->end(), x);
			// }
			
			// void sort()
			// {
			// 	ListNode<T>* temp = this->_base->_next;
			// 	while (temp->_next != this->_base)
			// 	{
			// 		if (temp->_value > temp->_next->_value)
			// 		{
			// 			this->swapNextNode(temp);
			// 			temp = this->_base->_next;
			// 		}
			// 		else
			// 			temp = temp->_next;
			// 	}
			// }

			// template <class Compare>
			// void sort (Compare comp)
			// {
			// 	ListNode<T>* temp = this->_base->_next;
			// 	while (temp->_next != this->_base)
			// 	{
			// 		if (comp(temp->_next->_value, temp->_value))
			// 		{
			// 			this->swapNextNode(temp);
			// 			temp = this->_base->_next;
			// 		}
			// 		else
			// 			temp = temp->_next;
			// 	}
			// }

			// void reverse()
			// {
			// 	this->changePrevNext(this->_base->_next);
			// }

	};

	// template <class T, class Alloc>
	// bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	
	// template <class T, class Alloc>
	// bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	
	// template <class T, class Alloc>
	// bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	
	// template <class T, class Alloc>
	// bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	
	// template <class T, class Alloc>
	// bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	
	// template <class T, class Alloc>
	// bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	// template <class T, class Alloc>
	// void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);


}

#endif