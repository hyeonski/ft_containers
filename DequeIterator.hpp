#ifndef DEQUEITERATOR_HPP
# define DEQUEITERATOR_HPP

# include "utils.hpp"

namespace ft
{
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