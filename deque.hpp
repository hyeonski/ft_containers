#ifndef DEQUE_HPP
# define DEQUE_HPP

# include <iostream>
# include "utils.hpp"
# include "iterator.hpp"
# include "DequeIterator.hpp"
# include "vector.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class deque
	{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef ft::DequeIterator<T, false> iterator;
			typedef ft::DequeIterator<T, true> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;
		private:
			typedef typename Alloc::template rebind< value_type* >::other Alarr;

			allocator_type _alloc;
			value_type** _arr;
			size_type _size;
			const size_type _blockSize = 256;

		public:
			explicit deque (const allocator_type& alloc = allocator_type());

			explicit deque (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

			template <class InputIterator>
			deque (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

			deque (const deque& x);

			virtual ~deque();

			deque& operator= (const deque& x);

			iterator begin();

			const_iterator begin() const;

			iterator end();

			const_iterator end() const;

			reverse_iterator rbegin();

			const_reverse_iterator rbegin() const;

			reverse_iterator rend();

			const_reverse_iterator rend() const;

			size_type size() const;

			size_type max_size() const;

			void resize (size_type n, value_type val = value_type());

			bool empty() const;

			reference operator[] (size_type n);

			const_reference operator[] (size_type n) const;

			reference at (size_type n);

			const_reference at (size_type n) const;

			reference front();

			const_reference front() const;

			reference back();

			const_reference back() const;

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last);

			void assign (size_type n, const value_type& val);

			void push_back (const value_type& val);

			void push_front (const value_type& val);

			void pop_back();

			void pop_front();

			iterator insert (iterator position, const value_type& val);

			void insert (iterator position, size_type n, const value_type& val);

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last);

			iterator erase (iterator position);

			iterator erase (iterator first, iterator last);

			void swap (deque& x);

			void clear();

			allocator_type get_allocator() const;



		private:
			template<class T, class Alloc = std::allocator<T> >
			class DequeBlock
			{
				private:
					const size_type _blockSize
				public:
					typedef T value_type;
					typedef Alloc allocator_type;
					typedef typename allocator_type::reference reference;
					typedef typename allocator_type::const_reference const_reference;
					typedef typename allocator_type::pointer pointer;
					typedef typename allocator_type::const_pointer const_pointer;
					typedef size_t size_type;

					value_type* _arr;
			};
	};


	template <class T, class Alloc>
	bool operator== (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator!= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<  (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>  (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs);

	template <class T, class Alloc>
	void swap (deque<T,Alloc>& x, deque<T,Alloc>& y);



}

#endif