#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "deque.hpp"

namespace ft
{
	template <class T, class Container = ft::deque<T> >
	class queue
	{
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

		private:
			container_type c;

		public:
			explicit queue (const container_type& ctnr = container_type()) : c(ctnr) {}

			queue(const queue& x) : c(x.c) {}

			virtual ~queue() {}

			queue& operator=(const queue& x)
			{
				if (this != &x)
					this->c = x.c;
				return (*this);
			}
			
			bool empty() const
			{
				return (this->c.empty());
			}

			size_type size() const
			{
				return (this->c.size());
			}

			value_type& front()
			{
				return (this->c.front());
			}

			const value_type& front() const
			{
				return (this->c.front());
			}

			value_type& back()
			{
				return (this->c.back());
			}

			const value_type& back() const
			{
				return (this->c.back());
			}

			void push (const value_type& val)
			{
				this->c.push_back(val);
			}

			void pop()
			{
				this->c.pop_front();
			}

			template <class U, class C>
			friend bool operator== (const queue<U,C>& lhs, const queue<U,C>& rhs);

			template <class U, class C>
			friend bool operator!= (const queue<U,C>& lhs, const queue<U,C>& rhs);

			template <class U, class C>
			friend bool operator<  (const queue<U,C>& lhs, const queue<U,C>& rhs);

			template <class U, class C>
			friend bool operator<= (const queue<U,C>& lhs, const queue<U,C>& rhs);

			template <class U, class C>
			friend bool operator>  (const queue<U,C>& lhs, const queue<U,C>& rhs);

			template <class U, class C>
			friend bool operator>= (const queue<U,C>& lhs, const queue<U,C>& rhs);
	};

	template <class T, class Container>
	bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs.c != rhs.c);
	}

	template <class T, class Container>
	bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template <class T, class Container>
	bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs.c > rhs.c);
	}

	template <class T, class Container>
	bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs.c >= rhs.c);
	}
}

#endif