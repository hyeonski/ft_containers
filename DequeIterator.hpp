#ifndef DEQUEITERATOR_HPP
# define DEQUEITERATOR_HPP

# include "utils.hpp"

namespace ft
{
	template<typename T, bool IsConst>
	class DequeBlockIterator
	{
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef typename choose<IsConst, const T &, T &>::type reference;
			typedef typename choose<IsConst, const T *, T *>::type pointer;	
			typedef ft::random_access_iterator_tag iterator_category;

			T* _ptr; // 고민해보자
			// commmon
			DequeBlockIterator(T* ptr = NULL) : _ptr(ptr) {}

			DequeBlockIterator(const DequeBlockIterator<T, false>& ref) : _ptr(ref._ptr) {}
			
			DequeBlockIterator& operator=(const DequeBlockIterator& ref)
			{
				if (this != &ref)
					this->_ptr = ref._ptr;
				return (*this);
			}

			virtual ~DequeBlockIterator() {}
			
			DequeBlockIterator& operator++()
			{
				++this->_ptr;
				return (*this);
			}

			DequeBlockIterator operator++(int)
			{
				DequeBlockIterator temp(*this);

				++this->_ptr;
				return (temp);
			}

			// input
			bool operator==(const DequeBlockIterator<T, true>& iter) const
			{
				return (this->_ptr == iter._ptr);
			}

			bool operator==(const DequeBlockIterator<T, false>& iter) const
			{
				return (this->_ptr == iter._ptr);
			}

			bool operator!=(const DequeBlockIterator<T, true>& iter) const
			{
				return (this->_ptr != iter._ptr);
			}

			bool operator!=(const DequeBlockIterator<T, false>& iter) const
			{
				return (this->_ptr != iter._ptr);
			}

			reference operator*() const
			{
				return (*this->_ptr);
			}

			pointer operator->() const
			{
				return (&(*this->_ptr));
			}

			// output

			// forward

			// bidirectional
			DequeBlockIterator& operator--()
			{
				--this->_ptr;
				return (*this);
			}

			DequeBlockIterator operator--(int)
			{
				DequeBlockIterator temp(*this);

				--this->_ptr;
				return (temp);
			}

			// random access
			DequeBlockIterator operator+(int n) const
			{
				return (DequeBlockIterator(this->_ptr + n));
			}

			difference_type operator+(const DequeBlockIterator<T, true> &iter) const
			{
				return (this->ptr + iter._ptr);
			}

			difference_type operator+(const DequeBlockIterator<T, false> &iter) const
			{
				return (this->ptr + iter._ptr);
			}

			DequeBlockIterator operator-(int n) const
			{
				return (DequeBlockIterator(this->_ptr - n));
			}

			difference_type operator-(const DequeBlockIterator<T, true> &iter) const
			{
				return (this->_ptr - iter._ptr);
			}

			difference_type operator-(const DequeBlockIterator<T, false> &iter) const
			{
				return (this->_ptr - iter._ptr);
			}

			DequeBlockIterator& operator+=(int n)
			{
				this->_ptr += n;
				return (*this);
			}

			DequeBlockIterator& operator-=(int n)
			{
				this->_ptr -= n;
				return (*this);
			}

			bool operator<  (const DequeBlockIterator<T, true>& rhs) const
			{
				return (this->_ptr < rhs._ptr);
			}

			bool operator<  (const DequeBlockIterator<T, false>& rhs) const
			{
				return (this->_ptr < rhs._ptr);
			}
			
			bool operator<= (const DequeBlockIterator<T, true>& rhs) const
			{
				return (this->_ptr <= rhs._ptr);
			}

			bool operator<= (const DequeBlockIterator<T, false>& rhs) const
			{
				return (this->_ptr <= rhs._ptr);
			}
			
			bool operator>  (const DequeBlockIterator<T, true>& rhs) const
			{
				return (this->_ptr > rhs._ptr);
			}

			bool operator>  (const DequeBlockIterator<T, false>& rhs) const
			{
				return (this->_ptr > rhs._ptr);
			}

			bool operator>= (const DequeBlockIterator<T, true>& rhs) const
			{
				return (this->_ptr >= rhs._ptr);
			}

			bool operator>= (const DequeBlockIterator<T, false>& rhs) const
			{
				return (this->_ptr >= rhs._ptr);
			}

			reference operator[](difference_type n) const
			{
				return (this->_ptr[n]);
			}
	};

	template <typename T, bool IsConst>
	DequeBlockIterator<T, IsConst> operator+ (typename DequeBlockIterator<T, IsConst>::difference_type n, const DequeBlockIterator<T, IsConst>& iter)
	{
		return (DequeBlockIterator<T, IsConst>(iter + n));
	}

	template<class T, class Alloc = std::allocator<T> > // 밀고 당길 때 편하려면 여유공간을 한 칸 두는게 편할지도
	class DequeBlock
	{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef ft::DequeBlockIterator<T, false> iterator;
			typedef ft::DequeBlockIterator<T, true> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;

		private:
			static const size_type _blockSize = 256;

		public:
			value_type* _arr;
			size_type _size;
			size_type _capacity;
			allocator_type _alloc;
			size_type _startIdx;


			DequeBlock(const allocator_type& alloc = allocator_type()) : _arr(NULL), _size(0), _capacity(0), _alloc(alloc), _startIdx(128)
			{
				this->_arr = this->_alloc.allocate(_blockSize);
				this->_capacity = _blockSize;
			}

			DequeBlock(const DequeBlock& x) : _arr(NULL), _size(x._size), _capacity(x._capacity), _alloc(x._alloc), _startIdx(x._startIdx)
			{
				this->_arr = this->_alloc.allocate(x._capacity);
				*this = x;
			}

			virtual ~DequeBlock()
			{
				for (size_type i = this->_startIdx; i < this->_startIdx + this->_size; ++i)
					this->_alloc.destroy(this->_arr + i);
				this->_alloc.deallocate(this->_arr, this->_capacity);
			}

			DequeBlock& operator=(const DequeBlock& x)
			{
				this->_reserveBack(x._capacity);
				this->clear();
				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_startIdx = x._startIdx;
				for (size_type i = x._startIdx; i < x._startIdx + x._size; ++i)
					this->_arr[i] = x._arr[i];
			}

			iterator begin()
			{
				return (iterator(this->_arr + this->_startIdx));
			}

			const_iterator begin() const
			{
				return (const_iterator(this->_arr + this->_startIdx));
			}

			iterator end()
			{
				return (iterator(this->_arr + this->_startIdx + this->_size));
			}

			const_iterator end() const
			{
				return (const_iterator(this->_arr + this->_startIdx + this->_size));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->_arr + this->_startIdx + this->_size));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->_arr + this->_startIdx + this->_size));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(this->_arr + this->_startIdx));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->_arr + this->_startIdx));
			}

			size_type size()
			{
				return (this->_size);
			}

			void clear()
			{
				for (size_type i = this->_startIdx; i < this->_startIdx + this->_size; ++i)
					this->_alloc.destory(this->_arr + i);
				this->_size = 0;
				this->_startIdx = this->_capacity / 2;
			}

			void push_back(const value_type& val)
			{
				if (this->_startIdx + this->_size >= this->_capacity)
					this->_reserveBack(this->_capacity * 2);
				this->_alloc.construct(this->_arr + this->_startIdx + this->_size, val);
				++this->_size;
			}

			void push_front(const value_type& val)
			{
				if (this->_startIdx == 0)
					this->_reserveFront(this->_capacity * 2);
				this->_alloc.construct(this->_arr + this->_startIdx - 1, val);
				--this->_startIdx;
				++this->_size;
			}

			void pop_back()
			{
				this->_alloc.destory(this->_arr + this->_startIdx + this->_size - 1);
				--this->_size;
			}

			void pop_front()
			{
				this->_alloc.destory(this->_arr + this->_startIdx);
				++this->_startIdx;
				--this->_size;
			}

			bool empty() const
			{
				return (this->_size == 0);
			}

			reference operator[] (size_type n)
			{
				return (this->_arr[this->_startIdx + n]);
			}
			
			const_reference operator[] (size_type n) const
			{
				return (this->_arr[this->_startIdx + n]);
			}

			reference at (size_type n)
			{
				if (this->_size <= n)
					throw std::out_of_range("Error: ft::vector: Index out of range");
				return (this->_arr[this->_startIdx + n]);
			}

			const_reference at (size_type n) const
			{
				if (this->_size <= n)
					throw std::out_of_range("Error: ft::vector: Index out of range");
				return (this->_arr[this->_startIdx + n]);
			}

			reference front()
			{
				return (this->_arr[this->_startIdx]);
			}

			const_reference front() const
			{
				return (this->_arr[this->_startIdx]);
			}

			reference back()
			{
				return (this->_arr[this->_startIdx + this->_size - 1]);
			}

			const_reference back() const
			{
				return (this->_arr[this->_startIdx + this->_size - 1]);
			}

			iterator insert (iterator position, const value_type& val)
			{
				size_type pos = position._ptr - this->_arr; // startIdx가지 감안되어 계산된 인덱스
				if (this->_startIdx + this->_size >= this->_capacity)
					this->_reserveBack(this->_capacity * 2);
				if (this->_size != 0)
					this->_shift_elem_back(pos, 1);
				++this->_size;
				this->_alloc.construct(this->_arr + pos, val);
				return (iterator(this->_arr + pos));
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				size_type pos = position._ptr - this->_arr;
				if (this->_capacity < this->_startIdx + this->_size + n)
				{
					if (this->_startIdx + this->_size + n > this->_capacity && this->_startIdx + this->_size + n < this->_capacity * 2)
						this->_reserveBack(this->_capacity * 2);
					else
						this->_reserveBack(this->_size + n);
				}
				this->_shift_elem_back(pos, n);
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
				if (this->_capacity < this->_startIdx + this->_size + n)
				{
					if (this->_startIdx + this->_size + n > this->_capacity && this->_startIdx + this->_size + n < this->_capacity * 2)
						this->_reserveBack(this->_capacity * 2);
					else
						this->_reserveBack(this->_size + n);
				}
				this->_shift_elem_back(pos, n);
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
				this->_shift_elem_front(pos, 1);
				--this->_size;
				return (position);
			}

			iterator erase (iterator first, iterator last)
			{
				size_type pos = first._ptr - this->_arr;
				size_type n = last - first;
				for (size_type i = 0; i < n; ++i)
					this->_alloc.destroy(this->_arr + pos + i);
				this->_shift_elem_front(pos, n);
				this->_size -= n;
				return (first);
			}

		private:
			void _reserveBack(size_type n)
			{
				if (n < this->_capacity)
					return ;
				T* temp = this->_alloc.allocate(n);
				for (size_type i = this->_startIdx; i < this->_size + this->_startIdx; ++i)
				{
					this->_alloc.construct(temp + i, this->_arr[i]);
					this->_alloc.destroy(this->_arr + i);
				}
				this->_alloc.deallocate(this->_arr, this->_capacity);
				this->_arr = temp;
				this->_capacity = n;
			}

			void _reserveFront(size_type n)
			{
				if (n < this->_capacity)
					return ;
				size_type expanded = n - this->_capacity;
				T* temp = this->_alloc.allocate(n);
				for (size_type i = this->_startIdx; i < this->_size + this->_startIdx; ++i)
				{
					this->_alloc.construct(temp + expanded + i, this->_arr[i]);
					this->_alloc.destroy(this->_arr + i);
				}
				this->_alloc.deallocate(this->_arr, this->_capacity);
				this->_arr = temp;
				this->_capacity = n;
				this->_startIdx += expanded;
			}

			void _shift_elem_back(size_type pos, size_type len)
			{
				size_type chunk_size = this->_startIdx + this->_size - pos;
				for (size_type i = 0; i < chunk_size; ++i)
					this->_arr[pos + len + chunk_size - i - 1] = this->_arr[pos + chunk_size - i - 1];
			}

			void _shift_elem_front(size_type pos, size_type len)
			{
				for (size_type i = 0; i < this->_startIdx + this->_size - pos - len; ++i)
					this->_arr[pos + i] = this->_arr[pos + i + len];
			}

	};

	











	template<typename T, bool IsConst>
	class DequeIterator
	{
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef typename choose<IsConst, const T &, T &>::type reference;
			typedef typename choose<IsConst, const T *, T *>::type pointer;	
			typedef ft::random_access_iterator_tag iterator_category;

			T* _ptr; // 고민해보자
			// commmon
			DequeIterator(T* ptr = NULL) : _ptr(ptr) {}

			DequeIterator(const DequeIterator<T, false>& ref) : _ptr(ref._ptr) {}
			
			DequeIterator& operator=(const DequeIterator& ref)
			{
				if (this != &ref)
					this->_ptr = ref._ptr;
				return (*this);
			}

			virtual ~DequeIterator() {}
			
			DequeIterator& operator++()
			{
				++this->_ptr;
				return (*this);
			}

			DequeIterator operator++(int)
			{
				DequeIterator temp(*this);

				++this->_ptr;
				return (temp);
			}

			// input
			bool operator==(const DequeIterator<T, true>& iter) const
			{
				return (this->_ptr == iter._ptr);
			}

			bool operator==(const DequeIterator<T, false>& iter) const
			{
				return (this->_ptr == iter._ptr);
			}

			bool operator!=(const DequeIterator<T, true>& iter) const
			{
				return (this->_ptr != iter._ptr);
			}

			bool operator!=(const DequeIterator<T, false>& iter) const
			{
				return (this->_ptr != iter._ptr);
			}

			reference operator*() const
			{
				return (*this->_ptr);
			}

			pointer operator->() const
			{
				return (&(*this->_ptr));
			}

			// output

			// forward

			// bidirectional
			DequeIterator& operator--()
			{
				--this->_ptr;
				return (*this);
			}

			DequeIterator operator--(int)
			{
				DequeIterator temp(*this);

				--this->_ptr;
				return (temp);
			}

			// random access
			DequeIterator operator+(int n) const
			{
				return (DequeIterator(this->_ptr + n));
			}

			difference_type operator+(const DequeIterator<T, true> &iter) const
			{
				return (this->ptr + iter._ptr);
			}

			difference_type operator+(const DequeIterator<T, false> &iter) const
			{
				return (this->ptr + iter._ptr);
			}

			DequeIterator operator-(int n) const
			{
				return (DequeIterator(this->_ptr - n));
			}

			difference_type operator-(const DequeIterator<T, true> &iter) const
			{
				return (this->_ptr - iter._ptr);
			}

			difference_type operator-(const DequeIterator<T, false> &iter) const
			{
				return (this->_ptr - iter._ptr);
			}

			DequeIterator& operator+=(int n)
			{
				this->_ptr += n;
				return (*this);
			}

			DequeIterator& operator-=(int n)
			{
				this->_ptr -= n;
				return (*this);
			}

			bool operator<  (const DequeIterator<T, true>& rhs) const
			{
				return (this->_ptr < rhs._ptr);
			}

			bool operator<  (const DequeIterator<T, false>& rhs) const
			{
				return (this->_ptr < rhs._ptr);
			}
			
			bool operator<= (const DequeIterator<T, true>& rhs) const
			{
				return (this->_ptr <= rhs._ptr);
			}

			bool operator<= (const DequeIterator<T, false>& rhs) const
			{
				return (this->_ptr <= rhs._ptr);
			}
			
			bool operator>  (const DequeIterator<T, true>& rhs) const
			{
				return (this->_ptr > rhs._ptr);
			}

			bool operator>  (const DequeIterator<T, false>& rhs) const
			{
				return (this->_ptr > rhs._ptr);
			}

			bool operator>= (const DequeIterator<T, true>& rhs) const
			{
				return (this->_ptr >= rhs._ptr);
			}

			bool operator>= (const DequeIterator<T, false>& rhs) const
			{
				return (this->_ptr >= rhs._ptr);
			}

			reference operator[](difference_type n) const
			{
				return (this->_ptr[n]);
			}
	};

	template <typename T, bool IsConst>
	DequeIterator<T, IsConst> operator+ (typename DequeIterator<T, IsConst>::difference_type n, const DequeIterator<T, IsConst>& iter)
	{
		return (DequeIterator<T, IsConst>(iter + n));
	}

	// typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	// {
	// 	return (lhs._base - rhs._base);
	// }
}

#endif