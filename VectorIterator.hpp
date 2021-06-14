#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include "utils.hpp"

namespace ft
{
	template<typename T>
	class VectorIterator
	{
		public:

			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;
			typedef const T& const_reference;
			// typedef Category iterator_category;

			T* _ptr; // 고민해보자
			// commmon
			template <typename U>
			VectorIterator(U* ptr = NULL) : _ptr((T*)ptr) {}
			template <typename U>
			VectorIterator(const VectorIterator<U>& ref) : _ptr((T*)ref._ptr) {}
			
			VectorIterator<T>& operator=(const VectorIterator<T>& ref)
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
			template <typename U>
			bool operator==(const VectorIterator<U>& iter) const
			{
				return (this->_ptr == (T*)iter._ptr);
			}

			template <typename U>
			bool operator!=(const VectorIterator<U>& iter) const
			{
				return (this->_ptr != (T*)iter._ptr);
			}

			reference operator*()
			{
				return (*this->_ptr);
			}

			const_reference operator*() const
			{
				return (*this->_ptr);
			}

			pointer operator->()
			{
				return (&(*this->_ptr));
			}

			const T* operator->() const
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
			VectorIterator operator+(int n) const;
			// +
			// -
			// -
			// <
			// >
			// <=
			// >=
			// +=
			// -=
			// []
	};


#endif