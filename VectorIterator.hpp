#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include "utils.hpp"

namespace ft
{
	template<typename T, bool IsConst>
	class VectorIterator
	{
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef typename choose<IsConst, const T &, T &>::type reference;
			typedef typename choose<IsConst, const T *, T *>::type pointer;	
			typedef ft::random_access_iterator_tag iterator_category;

			T* _ptr;
			// commmon
			VectorIterator(T* ptr = NULL) : _ptr(ptr) {}

			VectorIterator(const VectorIterator<T, false>& ref) : _ptr(ref._ptr) {}
			
			VectorIterator& operator=(const VectorIterator& ref)
			{
				if (this != &ref)
					this->_ptr = ref._ptr;
				return (*this);
			}

			virtual ~VectorIterator() {}
			
			VectorIterator& operator++()
			{
				++this->_ptr;
				return (*this);
			}

			VectorIterator operator++(int)
			{
				VectorIterator temp(*this);

				++this->_ptr;
				return (temp);
			}

			// input
			bool operator==(const VectorIterator<T, true>& iter) const
			{
				return (this->_ptr == iter._ptr);
			}

			bool operator==(const VectorIterator<T, false>& iter) const
			{
				return (this->_ptr == iter._ptr);
			}

			bool operator!=(const VectorIterator<T, true>& iter) const
			{
				return (this->_ptr != iter._ptr);
			}

			bool operator!=(const VectorIterator<T, false>& iter) const
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
			VectorIterator& operator--()
			{
				--this->_ptr;
				return (*this);
			}

			VectorIterator operator--(int)
			{
				VectorIterator temp(*this);

				--this->_ptr;
				return (temp);
			}

			// random access
			VectorIterator operator+(int n) const
			{
				return (VectorIterator(this->_ptr + n));
			}

			VectorIterator operator-(int n) const
			{
				return (VectorIterator(this->_ptr - n));
			}

			difference_type operator-(const VectorIterator<T, true> &iter) const
			{
				return (this->_ptr - iter._ptr);
			}

			difference_type operator-(const VectorIterator<T, false> &iter) const
			{
				return (this->_ptr - iter._ptr);
			}

			VectorIterator& operator+=(int n)
			{
				this->_ptr += n;
				return (*this);
			}

			VectorIterator& operator-=(int n)
			{
				this->_ptr -= n;
				return (*this);
			}

			bool operator<  (const VectorIterator<T, true>& rhs) const
			{
				return (this->_ptr < rhs._ptr);
			}

			bool operator<  (const VectorIterator<T, false>& rhs) const
			{
				return (this->_ptr < rhs._ptr);
			}
			
			bool operator<= (const VectorIterator<T, true>& rhs) const
			{
				return (this->_ptr <= rhs._ptr);
			}

			bool operator<= (const VectorIterator<T, false>& rhs) const
			{
				return (this->_ptr <= rhs._ptr);
			}
			
			bool operator>  (const VectorIterator<T, true>& rhs) const
			{
				return (this->_ptr > rhs._ptr);
			}

			bool operator>  (const VectorIterator<T, false>& rhs) const
			{
				return (this->_ptr > rhs._ptr);
			}

			bool operator>= (const VectorIterator<T, true>& rhs) const
			{
				return (this->_ptr >= rhs._ptr);
			}

			bool operator>= (const VectorIterator<T, false>& rhs) const
			{
				return (this->_ptr >= rhs._ptr);
			}

			reference operator[](difference_type n) const
			{
				return (this->_ptr[n]);
			}
	};

	template <typename T, bool IsConst>
	VectorIterator<T, IsConst> operator+ (typename VectorIterator<T, IsConst>::difference_type n, const VectorIterator<T, IsConst>& iter)
	{
		return (VectorIterator<T, IsConst>(iter + n));
	}
}

#endif