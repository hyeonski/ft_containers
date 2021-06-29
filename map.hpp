#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include "utils.hpp"
# include "iterator.hpp"
# include "RBTree.hpp"

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
			class value_compare
			{
				protected:
					Compare comp;
				
				public:
					value_compare (Compare c) : comp(c) {}
					typedef bool	result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef typename RBTree<value_type, value_compare, allocator_type>::iterator iterator;
			typedef typename RBTree<value_type, value_compare, allocator_type>::const_iterator const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;

		private:
			typedef typename Alloc::template rebind< RBTree<value_type, value_compare, allocator_type> >::other AlTree;
			typedef typename RBTree<value_type, value_compare, allocator_type>::TreeNode TreeNode;

			key_compare _comp;
			allocator_type _alloc;
			size_type _size;
			RBTree<value_type, value_compare, allocator_type>* _tree;

		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _size(0)
			{
				AlTree _treeAlloc;
				this->_tree = _treeAlloc.allocate(1);
				_treeAlloc.construct(this->_tree, RBTree<value_type, value_compare, allocator_type>(value_compare(this->_comp), false));
			}

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _size(0)
			{
				AlTree _treeAlloc;
				this->_tree = _treeAlloc.allocate(1);
				_treeAlloc.construct(this->_tree, RBTree<value_type, value_compare, allocator_type>(value_compare(this->_comp), false));
				this->insert(first, last);
			}

			map (const map& x) : _comp(x._comp), _alloc(x._alloc), _size(x._size)
			{
				AlTree _treeAlloc;
				this->_tree = _treeAlloc.allocate(1);
				_treeAlloc.construct(this->_tree, *(x._tree));
			}

			virtual ~map()
			{
				AlTree _treeAlloc;
				_treeAlloc.destroy(this->_tree);
				_treeAlloc.deallocate(this->_tree, 1);
			}

			map& operator= (const map& x)
			{
				if (this != &x)
				{
					*(this->_tree) = *(x._tree);
					this->_size = x._size;
				}
				return (*this);
			}

			iterator begin()
			{
				return (iterator(this->_tree->getMinNode(this->_tree->_root), this->_tree));
			}

			const_iterator begin() const
			{
				return (const_iterator(this->_tree->getMinNode(this->_tree->_root), this->_tree));
			}

			iterator end()
			{
				return (iterator(this->_tree->_leaf, this->_tree));
			}

			const_iterator end() const
			{
				return (const_iterator(this->_tree->_leaf, this->_tree));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(iterator(this->_tree->_leaf, this->_tree)));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(const_iterator(this->_tree->_leaf, this->_tree)));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(iterator(this->_tree->getMinNode(this->_tree->_root), this->_tree)));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(const_iterator(this->_tree->getMinNode(this->_tree->_root), this->_tree)));
			}

			bool empty() const
			{
				return (this->_size == 0);
			}

			size_type size() const
			{
				return (this->_size);
			}

			size_type max_size() const
			{
				return (this->_tree->_nodeAlloc.max_size());
			}

			mapped_type& operator[] (const key_type& k)
			{
				return ( (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second );
			}

			pair<iterator,bool> insert (const value_type& val)
			{
				pair<TreeNode*, bool> result = this->_tree->insert(val);
				
				if (result.second == true)
				{
					++this->_size;
					return (pair<iterator,bool>(iterator(result.first, this->_tree), true));
				}
				else
					return (pair<iterator,bool>(iterator(result.first, this->_tree), false));
			}

			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				return (this->insert(val).first);
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					this->insert(*first);
					++first;
				}
			}

			void erase (iterator position)
			{
				this->_tree->erase(position._ptr);
				--this->_size;
			}

			size_type erase (const key_type& k)
			{
				int erase_size = this->_tree->erase(value_type(k, mapped_type()));
				this->_size -= erase_size;
				return (erase_size);
			}

			void erase (iterator first, iterator last)
			{
				iterator next;
				for (iterator it = first; it != last;)
				{
					next = it++;
					this->erase(next);
				}
			}

			void swap (map& x)
			{
				char buf[sizeof(map)];
				memcpy(buf, reinterpret_cast<void *>(&x), sizeof(map));
				memcpy(reinterpret_cast<char *>(&x), reinterpret_cast<void *>(this), sizeof(map));
				memcpy(reinterpret_cast<char *>(this), reinterpret_cast<void *>(buf), sizeof(map));
			}

			void clear()
			{
				this->_tree->clearTree(this->_tree->_root);
				this->_size = 0;
			}

			key_compare key_comp() const
			{
				return (this->_comp);
			}

			value_compare value_comp() const
			{
				return (value_compare(this->_comp));
			}

			iterator find (const key_type& k)
			{
				return (iterator(this->_tree->find(value_type(k, mapped_type() )), this->_tree) );
			}

			const_iterator find (const key_type& k) const
			{
				return (const_iterator(this->_tree->find(value_type(k, mapped_type() )), this->_tree) );
			}

			size_type count (const key_type& k) const
			{
				if (this->find(k) == this->end())
					return (0);
				return (1);
			}

			iterator lower_bound (const key_type& k)
			{
				return (iterator(this->_tree->lowerBound(this->_tree->_root, value_type(k, mapped_type()), this->_tree->_leaf), this->_tree));
			}

			const_iterator lower_bound (const key_type& k) const
			{
				return (const_iterator(this->_tree->lowerBound(this->_tree->_root, value_type(k, mapped_type()), this->_tree->_leaf), this->_tree));
			}

			iterator upper_bound (const key_type& k)
			{
				return (iterator(this->_tree->upperBound(this->_tree->_root, value_type(k, mapped_type()), this->_tree->_leaf), this->_tree));
			}

			const_iterator upper_bound (const key_type& k) const
			{
				return (const_iterator(this->_tree->upperBound(this->_tree->_root, value_type(k, mapped_type()), this->_tree->_leaf), this->_tree));
			}

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return pair<const_iterator, const_iterator>(this->lower_bound(k), this->upper_bound(k));
			}

			pair<iterator,iterator>             equal_range (const key_type& k)
			{
				return pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k));
			}

			allocator_type get_allocator() const
			{
				return (this->_alloc);
			}

	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return ((lhs == rhs) || (lhs < rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs <= rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return ((lhs == rhs) || (lhs > rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	void swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}


}
#endif