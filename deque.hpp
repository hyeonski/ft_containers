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
			typedef ft::DequeIterator<T, Alloc, false> iterator;
			typedef ft::DequeIterator<T, Alloc, true> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;
		private:
			typedef typename Alloc::template rebind< DequeBlock<value_type, allocator_type> >::other AlBlock;
			typedef typename Alloc::template rebind< DequeBlock<value_type, allocator_type>* >::other AlBlockPtr;
			typedef DequeBlock<value_type, allocator_type> block_type;

			allocator_type _alloc;
			AlBlock _blockAlloc;
			ft::DequeBlock< block_type*, AlBlockPtr> _blocks;
			size_type _size;
			static const size_type _blockSize = 256;

		public:
			explicit deque (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0)
			{
				block_type* block = this->_blockAlloc.allocate(1);
				this->_blockAlloc.construct(block, block_type());
				this->_blocks.push_back(block);
			}

			explicit deque (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0)
			{
				block_type* block = this->_blockAlloc.allocate(1);
				this->_blockAlloc.construct(block, block_type());
				this->_blocks.push_back(block);
				this->assign(n, val);
			}

			template <class InputIterator>
			deque (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = NULL) : _alloc(alloc), _size(0)
			{
				block_type* block = this->_blockAlloc.allocate(1);
				this->_blockAlloc.construct(block, block_type());
				this->_blocks.push_back(block);
				this->assign(first, last);
			}

			deque (const deque& x) : _alloc(x._alloc), _size(0)
			{
				block_type* block = this->_blockAlloc.allocate(1);
				this->_blockAlloc.construct(block, block_type());
				this->_blocks.push_back(block);
				this->assign(x.begin(), x.end());
			}

			virtual ~deque()
			{
				this->clear();
				block_type* block = this->_blocks.front();
				this->_blockAlloc.destroy(block);
				this->_blockAlloc.deallocate(block, 1);
				this->_blocks.pop_back();
			}

			deque& operator= (const deque& x)
			{
				this->clear();
				this->assign(x.begin(), x.end());
			}

			iterator begin()
			{
				return (iterator(&this->front(), this))
			}

			const_iterator begin() const
			{
				return ()
			}

			iterator end()
			{
				return ()
			}

			const_iterator end() const
			{
				return ()
			}

			reverse_iterator rbegin();

			const_reverse_iterator rbegin() const;

			reverse_iterator rend();

			const_reverse_iterator rend() const;

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
					size_type newSize = this->_size - n;
					for (size_type i = 0; i < newSize; ++i)
						this->pop_back();
				}
				else
				{
					size_type newSize = n - this->_size;
					for (size_type i = 0; i < newSize; ++i)
						this->push_back();
				}
			}

			bool empty() const
			{
				return (this->_size == 0);
			}

			reference operator[] (size_type n)
			{
				if (n < this->_blocks.front()->size())
					return (*(this->_blocks.front())[n]);
				else
				{
					n -= this->_blocks.front()->size();
					size_type blockIdx = n / _blockSize;
					size_type elemIdx = n % _blockSize;
					return (*(this->_blocks[blockIdx + 1])[elemIdx]);
				}
			}

			const_reference operator[] (size_type n) const
			{
				if (n < this->_blocks.front()->size())
					return (*(this->_blocks.front())[n]);
				else
				{
					n -= this->_blocks.front()->size();
					size_type blockIdx = n / _blockSize;
					size_type elemIdx = n % _blockSize;
					return (*(this->_blocks[blockIdx + 1])[elemIdx]);
				}
			}

			reference at (size_type n)
			{
				if (n >= this->_size)
					throw std::out_of_range("Error: ft::deque: Index out of range");
				if (n < this->_blocks.front()->size())
					return (*(this->_blocks.front())[n]);
				else
				{
					n -= this->_blocks.front()->size();
					size_type blockIdx = n / _blockSize;
					size_type elemIdx = n % _blockSize;
					return (*(this->_blocks[blockIdx + 1])[elemIdx]);
				}
			}

			const_reference at (size_type n) const
			{
				if (n >= this->_size)
					throw std::out_of_range("Error: ft::deque: Index out of range");
				if (n < this->_blocks.front()->size())
					return (*(this->_blocks.front())[n]);
				else
				{
					n -= this->_blocks.front()->size();
					size_type blockIdx = n / _blockSize;
					size_type elemIdx = n % _blockSize;
					return (*(this->_blocks[blockIdx + 1])[elemIdx]);
				}
			}

			reference front()
			{
				return (this->_blocks.front()->front());
			}

			const_reference front() const
			{
				return (this->_blocks.front()->front());
			}

			reference back()
			{
				return (this->_blocks.back()->back());
			}

			const_reference back() const
			{
				return (this->_blocks.back()->back());
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
				block_type* last = this->_blocks.back();
				if (last->startIndex() + last->size() == _blockSize)
				{
					block_type* newBlock = this->_blockAlloc.allocate(1);
					this->_blockAlloc.construct(newBlock, block_type(0));
					newBlock->push_back(val);
					this->_blocks.push_back(newBlock);
				}
				else
					last->push_back(val);
				++this->_size;
			}

			void push_front (const value_type& val)
			{
				block_type* first = this->_blocks.front();
				if (first->startIndex() == 0)
				{
					block_type* newBlock = this->_blockAlloc.allocate(1);
					this->_blockAlloc.construct(newBlock, block_type(_blockSize - 1));
					newBlock->push_front(val);
					this->_blocks.push_front(newBlock);
				}
				else
					first->push_front(val);
				++this->_size;
			}

			void pop_back()
			{
				if (this->_blocks.back()->size() == 1)
				{
					if (this->_blocks.size() == 1)
						this->_blocks.back()->pop_back();
					block_type* last = this->_blocks.back();
					last->pop_back();
					this->_blockAlloc.destroy(last);
					this->_blockAlloc.deallocate(last, 1);
					this->_blocks.pop_back();
				}
				else
					this->_blocks.back()->pop_back();
				--this->_size;
			}

			void pop_front()
			{
				if (this->_blocks.front()->size() == 1)
				{
					if (this->_blocks.size() == 1)
						this->_blocks.front()->pop_front();
					block_type* first = this->_blocks.front();
					first->pop_front();
					this->_blockAlloc.destroy(first);
					this->_blockAlloc.deallocate(first, 1);
					this->_blocks.pop_front();
				}
				else
					this->_blocks.front()->pop_front();
				--this->_size;
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