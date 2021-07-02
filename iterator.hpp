#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
	class iterator_category {};
	class input_iterator_tag {};
	class output_iterator_tag {};
	class bidirectional_iterator_tag : public input_iterator_tag {};
	class random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Iterator>
	class iterator_traits
	{
		public:
			typedef typename Iterator::value_type value_type;
			typedef typename Iterator::difference_type difference_type;
			typedef typename Iterator::pointer pointer;
			typedef typename Iterator::reference reference;
			typedef typename Iterator::iterator_category iterator_category;
	};

	template <class T>
	class iterator_traits<T*>
	{
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;
			typedef random_access_iterator_tag iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef const T* pointer;
			typedef const T& reference;
			typedef random_access_iterator_tag iterator_category;
	};

	template <class Iterator>
	class reverse_iterator
	{
		public: 
			Iterator _base;
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
			typedef typename iterator_traits<Iterator>::value_type value_type;
			typedef typename iterator_traits<Iterator>::difference_type difference_type;
			typedef typename iterator_traits<Iterator>::pointer pointer;
			typedef typename iterator_traits<Iterator>::reference reference;

			reverse_iterator() {};
			
			explicit reverse_iterator (iterator_type it) : _base(it) {};
			
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base(rev_it._base) {}
			
			template <class Iter>
			reverse_iterator& operator=(const reverse_iterator<Iter>& rev_it)
			{
				this->_base = rev_it._base;
				return (*this);
			}

			iterator_type base() const
			{
				return (this->_base);
			}

			reference operator*() const
			{
				iterator_type temp(this->_base);
				--temp;
				return (*temp);
			}

			reverse_iterator operator+ (difference_type n) const
			{
				return (reverse_iterator(this->_base - n));
			}

			reverse_iterator& operator++()
			{
				--this->_base;
				return (*this);
			}

			reverse_iterator  operator++(int)
			{
				reverse_iterator temp(*this);
				--this->_base;
				return (temp);
			}

			reverse_iterator& operator+= (difference_type n)
			{
				this->_base = this->_base - n;
				return (*this);
			}

			reverse_iterator operator- (difference_type n) const
			{
				return (reverse_iterator(this->_base + n));
			}

			reverse_iterator& operator--()
			{
				++this->_base;
				return (*this);
			}

			reverse_iterator  operator--(int)
			{
				reverse_iterator temp(*this);
				++this->_base;
				return (temp);
			}

			reverse_iterator& operator-= (difference_type n)
			{
				this->_base = this->_base + n;
				return (*this);
			}

			pointer operator->() const
			{
				return (&(operator*()));
			}

			reference operator[](difference_type n) const
			{
				return (this->_base[-1 - n]);
			}
	};

	template <class Iter, class Iter2>
	bool operator== (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs._base == rhs._base);
	}

	template <class Iter, class Iter2>
	bool operator!= (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs._base != rhs._base);
	}

	template <class Iter, class Iter2>
	bool operator<  (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs._base > rhs._base);
	}
	
	template <class Iter, class Iter2>
	bool operator<= (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs._base >= rhs._base);
	}
	
	template <class Iter, class Iter2>
	bool operator>  (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs._base < rhs._base);
	}

	template <class Iter, class Iter2>
	bool operator>= (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs._base <= rhs._base);
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return (ft::reverse_iterator<Iterator>(rev_it + n));
	}

	template <class Iterator, class Iterator2>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (rhs._base - lhs._base);
	}
}

#endif









