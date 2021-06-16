#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include "utils.hpp"
# include "iterator.hpp"
# include "MapIterator.hpp"

namespace ft
{
	template <	class Key,                                     // map::key_type
				class T,                                       // map::mapped_type
				class Compare = ft::less<Key>,                     // map::key_compare
				class Alloc = std::allocator<ft::pair<const Key, T> >    // map::allocator_type
				>
	class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;

			typedef std::ptrdiff_t difference_type;
			typedef size_t size_type;

			typedef typename Alloc::template rebind< mapNode<Key, T> >::other Alnod;
		private:

		public:
	};


















	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef ft::VectorIterator<T, false> iterator;
			typedef ft::VectorIterator<T, true> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;

		private:
			T* _arr;
			size_t _size;
			size_t _capacity;
			Alloc _alloc;

			void expandCapacity()
			{
				if (this->_capacity == 0)
				{
					this->_arr = this->_alloc.allocate(1);
					this->_capacity = 1;
				}
				else
				{
					this->_capacity *= 2;
					T *temp = this->_alloc.allocate(this->_capacity);
					for (size_type i = 0; i < this->_size; i++)
					{
						this->_alloc.construct(temp + i, *(this->_arr + i) );
						this->_alloc.destroy(this->_arr + i);
					}
					this->_alloc.deallocate(this->_arr, this->_capacity / 2);
					this->_arr = temp;
				}
			}

			void shift_elem_back(size_type pos, size_type len)
			{
				size_type chunk_size = this->_size - pos;
				for (size_type i = 0; i < chunk_size; ++i)
					this->_arr[pos + len + chunk_size - i - 1] = this->_arr[pos + chunk_size - i - 1];
			}

			void shift_elem_front(size_type pos, size_type len)
			{
				for (size_type i = 0; i < this->_size - pos - len; ++i)
					this->_arr[pos + i] = this->_arr[pos + i + len];
			}

		public:
			explicit vector(const allocator_type& alloc = allocator_type()) : _arr(NULL), _size(0), _capacity(0), _alloc(alloc) {}

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _arr(NULL), _size(0), _capacity(0), _alloc(alloc)
			{
				assign(n, val);
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _arr(NULL), _size(0), _capacity(0), _alloc(alloc)
			{
				assign(first, last);
			}

			vector (const vector& x) : _arr(NULL), _size(0), _capacity(0), _alloc(x._alloc)
			{
				this->reserve(x._size);
				for (const_iterator iter = x.begin(); iter != x.end(); iter++)
					this->push_back(*iter);
			}

			virtual ~vector()
			{
				if (this->_capacity > 0)
				{
					this->clear();
					this->_alloc.deallocate(this->_arr, this->_capacity);
				}
			}

			vector& operator= (const vector& x)
			{
				if (this != &x)
				{
					this->reserve(x._size);
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

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->_arr + this->_size));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->_arr + this->_size));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(this->_arr));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->_arr));
			}

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
					if (n > this->_capacity && n < this->_capacity * 2)
						this->expandCapacity();
					else
						this->reserve(n);
					for (size_type i = this->_size; i < n; ++i)
						this->_alloc.construct(this->_arr + i, val);
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
					throw std::length_error("Error: ft::vector: Length is too long");
				if (this->_arr == NULL)
					this->_arr = this->_alloc.allocate(n);
				else
				{
					T* temp = this->_alloc.allocate(n);
					for (size_type i = 0; i < this->_size; i++)
					{
						this->_alloc.construct(temp + i, *(this->_arr + i));
						this->_alloc.destroy(this->_arr + i);
					}
					this->_alloc.deallocate(this->_arr, this->_capacity);
					this->_arr = temp;
				}
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
					throw std::out_of_range("Error: ft::vector: Index out of range");
				return (this->_arr[n]);
			}

			const_reference at (size_type n) const
			{
				if (this->_size <= n)
					throw std::out_of_range("Error: ft::vector: Index out of range");
				return (this->_arr[n]);
			}

			reference front()
			{
				return (this->_arr[0]);
			}

			const_reference front() const
			{
				return (this->_arr[0]);
			}

			reference back()
			{
				return (this->_arr[this->_size - 1]);
			}

			const_reference back() const
			{
				return (this->_arr[this->_size - 1]);
			}

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				this->clear();

				size_type n = 0;
				for (InputIterator iter = first; iter != last; ++iter)
					++n;
				this->reserve(n);
				for (InputIterator iter = first; iter != last; ++iter)
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
				if (this->_capacity <= this->_size)
					this->expandCapacity();
				this->_alloc.construct(this->_arr + this->_size, val);
				++this->_size;
			}

			void pop_back()
			{
				this->_alloc.destroy(this->_arr + (--this->_size));
			}

			iterator insert (iterator position, const value_type& val)
			{
				size_type pos = position._ptr - this->_arr;
				if (this->_size == this->_capacity)
					this->expandCapacity();
				if (this->_size != 0)
					this->shift_elem_back(pos, 1);
				this->_size += 1;
				this->_alloc.construct(this->_arr + pos, val);
				return (iterator(this->_arr + pos));
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				size_type pos = position._ptr - this->_arr;
				if (this->_capacity < this->_size + n)
				{
					if (this->_size + n > this->_capacity && this->_size + n < this->_capacity * 2)
						this->expandCapacity();
					else
						this->reserve(this->_size + n);
				}
				this->shift_elem_back(pos, n);
				this->_size += n;
				for (size_type i = 0; i < n; ++i)
					this->_alloc.construct(this->_arr + pos + i, val);
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				size_type pos = position._ptr - this->_arr;
				size_type n = 0;
				for (InputIterator temp = first; temp != last; ++temp)
					++n;
				if (this->_capacity < this->_size + n)
				{
					if (this->_size + n > this->_capacity && this->_size + n < this->_capacity * 2)
						this->expandCapacity();
					else
						this->reserve(this->_size + n);
				}
				this->shift_elem_back(pos, n);
				this->_size += n;
				for (size_type i = 0; i < n; ++i)
				{
					this->_alloc.construct(this->_arr + pos + i, *first);
					first++;
				}
			}

			iterator erase (iterator position)
			{
				size_type pos = position._ptr - this->_arr;
				this->_alloc.destroy(this->_arr + pos);
				this->shift_elem_front(pos, 1);
				this->_size -= 1;
				return (position);
			}

			iterator erase (iterator first, iterator last)
			{
				size_type pos = first._ptr - this->_arr;
				size_type n = last - first;
				for (size_type i = 0; i < n; ++i)
					this->_alloc.destroy(this->_arr + pos + i);
				this->shift_elem_front(pos, n);
				this->_size -= n;
				return (first);
			}

			void swap (vector& x)
			{
				vector<T> temp(*this);
				pointer temp_arr = this->_arr;
				
				this->_arr = x._arr;
				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_alloc = x._alloc;

				x._arr = temp_arr;
				x._size = temp._size;
				x._capacity = temp._capacity;
				x._alloc = temp._alloc;
			}

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

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));	
	}
	
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ((lhs == rhs) || (lhs < rhs));
	}
	
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs <= rhs));
	}
	
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ((lhs == rhs) || (lhs > rhs));
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}

}
#endif