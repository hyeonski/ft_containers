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
			T* _arr;
			size_t _size;
			size_t _capacity;
			Alloc _alloc;

			class length_error : public std::logic_error
			{
				public:
					explicit length_error (const std::string& what_arg);
			};

			class out_of_range : public logic_error
			{
				public:
					explicit out_of_range (const std::string& what_arg);
			};

			void expandCapacity()
			{
				if (this->_size <= this->_capacity)
					return ;
				if (this->_capacity == 0)
				{
					this->_arr = this->alloc.allocate(1);
					this->_capacity = 1;
				}
				else
				{
					this->_capacity *= 2;
					T *temp = this->alloc.allocate(this->_capacity);
					for (size_type i = 0; i < this->_size; i++)
					{
						this->alloc.construct(temp + i, *(this->_arr + i) );
						this->alloc.destroy(this->_arr + i);
					}
					this->alloc.deallocate(this->_arr, this->_capacity / 2);
					this->_arr = temp;
				}
			}

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

			virtual ~vector()
			{
				if (this->arr_capacity > 0)
				{
					this->clear();
					this->alloc.deallocate(this->arr, this->arr_capacity);
				}
			}

			vector& operator= (const vector& x)
			{
				if (this != &x)
				{
					this->reserve(x._capacity);
					assign(x.begin(), x.end());
				}
				return (*this);
			}

			iterator begin()
			{
				return (iterator(this->_arr));
			}

			const_iterator begin() const
			{
				return (const_iterator(this->_arr));
			}

			iterator end()
			{
				return (iterator(this->_arr + this->_size));
			}

			const_iterator end() const
			{
				return (const_iterator(this->_arr + this->_size));
			}

			// reverse_iterator rbegin()
			// {
			// 	// return (reverse/)
			// }

			// const_reverse_iterator rbegin() const;

			// reverse_iterator rend();

			// const_reverse_iterator rend() const;

			size_type size() const
			{
				return (this->_size);
			}

			size_type max_size() const
			{
				return (this->_alloc.max_size());
			}

			void resize (size_type n, value_type val = value_type())
			{
				if (n <= this->_size)
				{
					size_type size = this->_size - n;
					for (size_type i = 0; i < size; i++)
						this->pop_back();
				}
				else
				{
					this->capacityExpand();
					for (size_type i = this->_size; i < n; ++i)
						this->alloc.construct(this->_arr + i, val);
					this->_size = n;
				}
			}

			size_type capacity() const
			{
				return (this->_capacity);
			}

			bool empty() const
			{
				return (this->_size == 0);
			}

			void reserve (size_type n)
			{
				if (this->_capacity >= n)
					return ;
				if (this->max_size() < n)
					throw ft::length_error("Error: ft::vector: Length is too long");
				
				T* temp = this->_alloc.allocate(n);
				for (size_type i = 0; i < this->_size; i++)
				{
					this->_alloc.construct(temp + i, *(this->_arr + i));
					this->_alloc.destroy(this->_arr + i);
				}
				this->_alloc.deallocate(this->_arr, this->_capacity);

				this->_arr = temp;
				this->_capacity = n;
			}

			reference operator[] (size_type n)
			{
				return (this->_arr[n]);
			}

			const_reference operator[] (size_type n) const
			{
				return (this->_arr[n]);
			}

			reference at (size_type n)
			{
				if (this->_size <= n)
					throw ft::out_of_range("Error: ft::vector: Index out of range");
				return (this->_arr[n]);
			}

			const_reference at (size_type n) const
			{
				if (this->_size <= n)
					throw ft::out_of_range("Error: ft::vector: Index out of range");
				return (this->_arr[n]);
			}

			reference front()
			{
				return (this->arr[0]);
			}

			const_reference front() const
			{
				return (this->arr[0]);
			}

			reference back()
			{
				return (this->arr[arr_size - 1]);
			}

			const_reference back() const
			{
				return (this->arr[arr_size - 1]);
			}

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				this->clear();
				for (InputIterator iter = first, iter != last, iter++)
					this->push_back(*iter);
			}

			void assign (size_type n, const value_type& val)
			{
				this->clear();
				this->reserve(n);
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
			}

			void push_back (const value_type& val)
			{
				if (this->_capacity == this->_size)
					this->expandCapacity();
				this->_alloc.construct(this->_alloc + this->_size, val);
				++this->_size;
			}

			void pop_back()
			{
				this->_alloc.destroy(this->_arr + (--this->_size));
			}

			// iterator insert (iterator position, const value_type& val);

			// void insert (iterator position, size_type n, const value_type& val);

			// template <class InputIterator>
			// void insert (iterator position, InputIterator first, InputIterator last);

			// iterator erase (iterator position);

			// iterator erase (iterator first, iterator last);

			// void swap (vector& x);

			void clear()
			{
				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(this->_arr + i);
				this->_size = 0;
			}

			allocator_type get_allocator() const
			{
				return (this->_alloc);
			}

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