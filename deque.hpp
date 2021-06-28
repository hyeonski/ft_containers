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
			typedef typename Alloc::template rebind< value_type* >::other AlPtr;

			allocator_type _alloc;
			ft::DequeBlock< value_type*, AlPtr> _blocks;
			size_type _start;
			size_type _size;
			static const size_type _blockSize = (sizeof(value_type) < 256 ? (4096 / sizeof(value_type)) : 16);

		public:
			explicit deque (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _start(0), _size(0) {}

			explicit deque (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _start(0), _size(0)
			{
				this->assign(n, val);
			}

			template <class InputIterator>
			deque (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = NULL) : _alloc(alloc), _start(0), _size(0)
			{
				this->assign(first, last);
			}

			deque (const deque& x) : _alloc(x._alloc), _start(0), _size(0)
			{
				this->assign(x.begin(), x.end());
			}

			virtual ~deque()
			{
				this->clear();
				for (typename ft::DequeBlock< value_type*, AlPtr>::iterator iter = this->_blocks.begin(); iter != this->_blocks.end(); ++iter)
					this->_alloc.deallocate(*iter, _blockSize);
				this->_blocks.clear();
			}

			deque& operator= (const deque& x)
			{
				this->clear();
				this->assign(x.begin(), x.end());
			}

			iterator begin()
			{
				value_type** block = &(this->_blocks.front()) + (this->_start / _blockSize);
				return (iterator(*block + (this->_start % _blockSize), this->empty() ? 0 : block));
			}

			const_iterator begin() const
			{
				value_type** block = &(this->_blocks.front()) + (this->_start / _blockSize);
				return (const_iterator(*block + (this->_start % _blockSize), this->empty() ? 0 : block));
			}

			iterator end()
			{
				size_type pos = this->_start + this->_size;
				value_type** block = &(this->_blocks.front()) + (pos / _blockSize);
				return (iterator(*block + (pos % _blockSize), this->empty() ? 0 : block));
			}

			const_iterator end() const
			{
				size_type pos = this->_start + this->_size;
				value_type** block = &(this->_blocks.front()) + (pos / _blockSize);
				return (const_iterator(*block + (pos % _blockSize), this->empty() ? 0 : block));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->end()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->begin()));
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
					size_type toDelete = this->_size - n;
					for (size_type i = 0; i < toDelete; ++i)
						this->pop_back();
				}
				else
				{
					size_type toAdd = n - this->_size;
					for (size_type i = 0; i < toAdd; ++i)
						this->push_back();
				}
			}

			bool empty() const
			{
				return (this->_size == 0);
			}

			reference operator[] (size_type n)
			{
				size_type pos = this->_start + n;
				value_type* block = this->_blocks[pos / _blockSize];
				return (block[pos % _blockSize]);
			}

			const_reference operator[] (size_type n) const
			{
				size_type pos = this->_start + n;
				value_type* block = this->_blocks[pos / _blockSize];
				return (block[pos % _blockSize]);
			}

			reference at (size_type n)
			{
				if (this->_size <= n)
					throw std::out_of_range("Error: ft::deque: Index out of range");
				size_type pos = this->_start + n;
				value_type* block = this->_blocks[pos / _blockSize];
				return (block[pos % _blockSize]);
			}

			const_reference at (size_type n) const
			{
				if (this->_size <= n)
					throw std::out_of_range("Error: ft::deque: Index out of range");
				size_type pos = this->_start + n;
				value_type* block = this->_blocks[pos / _blockSize];
				return (block[pos % _blockSize]);
			}

			reference front()
			{
				value_type* block = this->_blocks[this->_start / _blockSize];
				return (block[this->_start % _blockSize]);
			}

			const_reference front() const
			{
				value_type* block = this->_blocks[this->_start / _blockSize];
				return (block[this->_start % _blockSize]);
			}

			reference back()
			{
				size_type last = this->_start + this->_size - 1;
				value_type* block = this->_blocks[last / _blockSize];
				return (block[last % _blockSize]);
			}

			const_reference back() const
			{
				size_type last = this->_start + this->_size - 1;
				value_type* block = this->_blocks[last / _blockSize];
				return (block[last % _blockSize]);
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
			}

			void push_back (const value_type& val)
			{
				if (this->_getBackSpare() == 0)
					this->_addBackCapacity();
				size_type toAdd = this->_start + this->_size;
				value_type* block = this->_blocks[toAdd / _blockSize];
				this->_alloc.construct(block + (toAdd % _blockSize), val);
				++this->_size;
			}

			void push_front (const value_type& val)
			{
				if (this->_getFrontSpare() == 0)
					this->_addFrontCapacity();
				value_type* block = this->_blocks[this->_start / _blockSize];
				--this->_start;
				this->_alloc.construct(block + (this->_start % _blockSize), val);
				++this->_size;
			}

			void pop_back()
			{
				size_type last = this->_start + this->_size - 1;
				value_type* block = this->_blocks[last / _blockSize];
				this->_alloc.destroy(block + (last % _blockSize));

				--this->_size;
				this->removeBackSpare();
			}

			void pop_front()
			{
				value_type* block = this->_blocks[this->_start / _blockSize];
				this->_alloc.destroy(block + (this->_start % _blockSize));
				--this->_size;
				++this->_start;
				this->removeFrontSpare();
			}

			// iterator insert (iterator position, const value_type& val) // begin 또는 end에 삽입 시 pointer valid
			// {
			// 	if (position == this->begin())
			// 		this->push_front(val);
			// 	else if (position == this->end())
			// 		this->push_back(val);
			// 	else
			// 	{
					
			// 	}
			// }

			// void insert (iterator position, size_type n, const value_type& val)
			// {
			// 	if (position == this->begin())
			// 	{
			// 		for (size_type i = 0; i < n; ++i)
			// 			this->push_front(val);
			// 	}
			// 	else if (position == this->end())
			// 	{
			// 		for (size_type i = 0; i < n; ++i)
			// 			this->push_back(val);
			// 	}
			// 	else
			// 	{
					
			// 	}
			// }

			// template <class InputIterator>
			// void insert (iterator position, InputIterator first, InputIterator last);

			// iterator erase (iterator position)
			// {
			// 	if (position == this->begin())
			// 		this->pop_front(val);
			// 	else if (position == this->end())
			// 		this->pop_back(val);
			// 	else
			// 	{

			// 	}
			// }

			// iterator erase (iterator first, iterator last);

			// void swap (deque& x)
			// {
			// 	char buf[sizeof(deque)];
			// 	memcpy(buf, reinterpret_cast<void *>(&x), sizeof(deque));
			// 	memcpy(reinterpret_cast<char *>(&x), reinterpret_cast<void *>(this), sizeof(deque));
			// 	memcpy(reinterpret_cast<char *>(this), reinterpret_cast<void *>(buf), sizeof(deque));

			// }

			void clear()
			{
				while (this->_size > 0)
					this->pop_back();
			}

			allocator_type get_allocator() const
			{
				return (this->_alloc);
			}

		private:
			size_type _getCapacity()
			{
				return (this->_blocks.size() == 0 ? 0 : this->_blocks.size() * _blockSize - 1);
			}
			size_type _getFrontSpare()
			{
				return (this->_start);
			}

			size_type _getBackSpare()
			{
				return (this->_getCapacity() - (this->_start + this->_size));
			}

			void _addBackCapacity()
			{
				value_type* newBlock = this->_alloc.allocate(_blockSize);
				this->_blocks.push_back(newBlock);
			}

			void _addFrontCapacity()
			{
				value_type* newBlock = this->_alloc.allocate(_blockSize);
				this->_blocks.push_front(newBlock);

				if (this->_blocks.size() == 1)
					this->_start = _blockSize / 2;
				else
					this->_start += _blockSize;
			} 

			size_type _getFrontSpareBlock()
			{
				return (this->_getFrontSpare() / _blockSize);
			}

			size_type _getBackSpareBlock()
			{
				return (this->_getBackSpare() / _blockSize);
			}

			bool removeFrontSpare()
			{
				if (this->_getFrontSpareBlock() >= 2)
				{
					this->_alloc.deallocate(this->_blocks.front(), _blockSize);
					this->_blocks.pop_front();
					this-_start -= _blockSize;
					return (true);
				}
				return (false);
			}

			bool removeBackSpare()
			{
				if (this->_getBackSpareBlock() >= 2)
				{
					std::cout << this->_blocks.size() << std::endl;
					this->_alloc.deallocate(this->_blocks.back(), _blockSize);
					this->_blocks.pop_back();
					return (true);
				}
				return (false);
			}


	};


	template <class T, class Alloc>
	bool operator== (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));	
	}

	template <class T, class Alloc>
	bool operator<  (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs)
	{
		return ((lhs == rhs) || (lhs < rhs));
	}

	template <class T, class Alloc>
	bool operator>  (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs)
	{
		return (!(lhs <= rhs));
	}

	template <class T, class Alloc>
	bool operator>= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs)
	{
		return ((lhs == rhs) || (lhs > rhs));
	}

	template <class T, class Alloc>
	void swap (deque<T,Alloc>& x, deque<T,Alloc>& y)
	{
		x.swap(y);
	}

}

#endif