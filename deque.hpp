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
				return (*this);
			}

			iterator begin()
			{
				value_type** block = const_cast<value_type**>(&(this->_blocks.front())) + (this->_start / _blockSize);
				return (iterator(*block + (this->_start % _blockSize), this->empty() ? 0 : block));
			}

			const_iterator begin() const
			{
				value_type** block = const_cast<value_type**>(&(this->_blocks.front())) + (this->_start / _blockSize);
				return (const_iterator(*block + (this->_start % _blockSize), this->empty() ? 0 : block));
			}

			iterator end()
			{
				size_type pos = this->_start + this->_size;
				value_type** block = const_cast<value_type**>(&(this->_blocks.front())) + (pos / _blockSize);
				return (iterator(*block + (pos % _blockSize), this->empty() ? 0 : block));
			}

			const_iterator end() const
			{
				size_type pos = this->_start + this->_size;
				value_type** block = const_cast<value_type**>(&(this->_blocks.front())) + (pos / _blockSize);
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
						this->push_back(val);
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
					throw std::out_of_range("deque");
				size_type pos = this->_start + n;
				value_type* block = this->_blocks[pos / _blockSize];
				return (block[pos % _blockSize]);
			}

			const_reference at (size_type n) const
			{
				if (this->_size <= n)
					throw std::out_of_range("deque");
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
				--this->_start;
				value_type* block = this->_blocks[this->_start / _blockSize];
				this->_alloc.construct(block + (this->_start % _blockSize), val);
				++this->_size;
			}

			void pop_back()
			{
				size_type last = this->_start + this->_size - 1;
				value_type* block = this->_blocks[last / _blockSize];
				this->_alloc.destroy(block + (last % _blockSize));

				--this->_size;
				this->_removeBackSpare();
			}

			void pop_front()
			{
				value_type* block = this->_blocks[this->_start / _blockSize];
				this->_alloc.destroy(block + (this->_start % _blockSize));
				--this->_size;
				++this->_start;
				this->_removeFrontSpare();
			}

			iterator insert (iterator position, const value_type& val) // begin 또는 end에 삽입 시 pointer valid
			{
				size_type pos = position - this->begin();
				size_type toEnd = this->size() - pos;
				if (pos < toEnd)
				{   // insert by shifting things backward
					if (this->_getFrontSpare() == 0)
						this->_addFrontCapacity();
					if (pos == 0) // position == begin
						this->push_front(val);
					else
					{
						this->_shift_elem_front(--this->begin(), this->begin(), position);
						--this->_start;
						value_type* block = this->_blocks[(this->_start + pos) / _blockSize];
						this->_alloc.construct(block + ((this->_start + pos) % _blockSize), val);
						++this->_size;
					}
				}
				else
				{   // insert by shifting things forward
					if (this->_getBackSpare() == 0)
						this->_addBackCapacity();
					if (toEnd == 0)
						this->push_back(val);
					else
					{
						this->_shift_elem_back(++this->end(), this->end(), position);
						value_type* block = this->_blocks[(this->_start + pos) / _blockSize];
						this->_alloc.construct(block + ((this->_start + pos) % _blockSize), val);
						++this->_size;
					}
				}
				return (this->begin() + pos);
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				size_type pos = position - this->begin();
				size_type toEnd = this->size() - pos;
				if (pos < toEnd)
				{   // insert by shifting things backward
					while (this->_getFrontSpare() < n)
						this->_addFrontCapacity();
					if (pos == 0) // position == begin
					{
						for (size_type i = 0; i < n; ++i)
							this->push_front(val);
					}
					else
					{
						this->_shift_elem_front(this->begin() - n, this->begin(), position);
						this->_start -= n;

						value_type* block;
						for (size_type i = 0; i < n; ++i)
						{
							block = this->_blocks[(this->_start + pos + i) / _blockSize];
							this->_alloc.construct(block + ((this->_start + pos + i) % _blockSize), val);
						}
						this->_size += n;
					}
				}
				else
				{   // insert by shifting things forward
					if (this->_getBackSpare() < n)
						this->_addBackCapacity();
					if (toEnd == 0)
					{
						for (size_type i = 0; i < n; ++i)
							this->push_back(val);
					}
					else
					{
						this->_shift_elem_back(this->end() + n, this->end(), position);

						value_type* block;
						for (size_type i = 0; i < n; ++i)
						{
							block = this->_blocks[(this->_start + pos + i) / _blockSize];
							this->_alloc.construct(block + ((this->_start + pos + i) % _blockSize), val);
						}
						this->_size += n;
					}
				}
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = NULL)
			{
				size_type pos = position - this->begin();
				size_type toEnd = this->size() - pos;
				size_type n = 0;
				for (InputIterator temp = first; temp != last; ++temp)
					++n;
				if (pos < toEnd)
				{   // insert by shifting things backward
					while (this->_getFrontSpare() < n)
						this->_addFrontCapacity();
					if (pos != 0)
						this->_shift_elem_front(this->begin() - n, this->begin(), position);

					this->_start -= n;

					value_type* block;
					for (size_type i = 0; i < n; ++i)
					{
						block = this->_blocks[(this->_start + pos + i) / _blockSize];
						this->_alloc.construct(block + ((this->_start + pos + i) % _blockSize), *first);
						++first;
					}
					this->_size += n;
				}
				else
				{   // insert by shifting things forward
					if (this->_getBackSpare() < n)
						this->_addBackCapacity();
					if (toEnd != 0)
						this->_shift_elem_back(this->end() + n, this->end(), position);

					value_type* block;
					for (size_type i = 0; i < n; ++i)
					{
						block = this->_blocks[(this->_start + pos + i) / _blockSize];
						this->_alloc.construct(block + ((this->_start + pos + i) % _blockSize), *first);
						++first;
					}
					this->_size += n;
				}
			}

			iterator erase (iterator position)
			{
				iterator begin = this->begin();
				difference_type pos = position - begin;

				this->_alloc.destroy(position._ptr);

				if (static_cast<size_type>(pos) <= (this->_size - 1) / 2)
				{   // erase from front
					this->_shift_elem_back(position + 1, position, begin);
					--this->_size;
					++this->_start;
					this->_removeFrontSpare();
				}
				else
				{   // erase from back
					this->_shift_elem_front(position, position + 1, this->end());
					--this->_size;
					this->_removeBackSpare();
				}
				return (this->begin() + pos);
			}

			iterator erase (iterator first, iterator last)
			{
				iterator begin = this->begin();
				difference_type pos = first - begin;
				size_type n = last - first;

				iterator temp = first;
				while (temp != last)
				{
					this->_alloc.destroy(temp._ptr);
					++temp;
				}

				if (static_cast<size_type>(pos) <= (this->_size - 1) / 2)
				{
					this->_shift_elem_back(last, first, begin);
					this->_size -= n;
					this->_start += n;
					this->_removeFrontSpare();
				}
				else
				{   // erase from back
					this->_shift_elem_front(first, last, this->end());
					this->_size -= n;
					this->_removeBackSpare();
				}
				return (this->begin() + pos);
			}

			void swap (deque& x)
			{
				char buf[sizeof(deque)];
				memcpy(buf, reinterpret_cast<void *>(&x), sizeof(deque));
				memcpy(reinterpret_cast<char *>(&x), reinterpret_cast<void *>(this), sizeof(deque));
				memcpy(reinterpret_cast<char *>(this), reinterpret_cast<void *>(buf), sizeof(deque));

			}

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

			bool _removeFrontSpare()
			{
				if (this->_getFrontSpareBlock() >= 2)
				{
					this->_alloc.deallocate(this->_blocks.front(), _blockSize);
					this->_blocks.pop_front();
					this->_start -= _blockSize;
					return (true);
				}
				return (false);
			}

			bool _removeBackSpare()
			{
				if (this->_getBackSpareBlock() >= 2)
				{
					this->_alloc.deallocate(this->_blocks.back(), _blockSize);
					this->_blocks.pop_back();
					return (true);
				}
				return (false);
			}

			void _shift_elem_front(iterator newFront, iterator oldFront, iterator pos)
			{
				while (oldFront != pos)
				{
					this->_alloc.construct(newFront._ptr, *oldFront);
					this->_alloc.destroy(oldFront._ptr);
					++newFront;
					++oldFront;
				}
			}

			void _shift_elem_back(iterator newEnd, iterator oldEnd, iterator pos)
			{
				if (oldEnd == pos)
					return ;
				do
				{
					--newEnd;
					--oldEnd;
					this->_alloc.construct(newEnd._ptr, *oldEnd);
					this->_alloc.destroy(oldEnd._ptr);
				} while (oldEnd != pos);
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