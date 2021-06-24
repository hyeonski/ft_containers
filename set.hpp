#ifndef SET_HPP
# define SET_HPP

# include <iostream>
# include "utils.hpp"
# include "iterator.hpp"
# include "RBTree.hpp"

namespace ft
{
	template <	class T,                        // set::key_type/value_type
				class Compare = ft::less<T>,        // set::key_compare/value_compare
				class Alloc = std::allocator<T>      // set::allocator_type
				>
	class set
	{
		public:
			typedef T key_type;
			typedef T value_type;
			typedef const value_type const_value_type;
			typedef Compare key_compare;
			typedef Compare value_compare;
			typedef Alloc allocator_type;
			typedef typename Alloc::template rebind< const_value_type >::other const_allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef typename RBTree<const_value_type, value_compare, const_allocator_type>::const_iterator iterator;
			typedef typename RBTree<const_value_type, value_compare, const_allocator_type>::const_iterator const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;

			typedef typename Alloc::template rebind< RBTree<const_value_type, value_compare, const_allocator_type> >::other AlTree;
			typedef typename RBTree<const_value_type, value_compare, const_allocator_type>::TreeNode TreeNode;

		private:
			key_compare _comp;
			allocator_type _alloc;
			size_type _size;
			RBTree<const_value_type, value_compare, const_allocator_type>* _tree;

		public:
			explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _size(0)
			{
				AlTree _treeAlloc;
				this->_tree = _treeAlloc.allocate(1);
				_treeAlloc.construct(this->_tree, RBTree<const_value_type, value_compare, const_allocator_type>(value_compare(this->_comp), false));
			}

			template <class InputIterator>
			set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _size(0)
			{
				AlTree _treeAlloc;
				this->_tree = _treeAlloc.allocate(1);
				_treeAlloc.construct(this->_tree, RBTree<const_value_type, value_compare, const_allocator_type>(value_compare(this->_comp), false));
				this->insert(first, last);
			}

			set (const set& x) : _comp(x._comp), _alloc(x._alloc), _size(x._size)
			{
				AlTree _treeAlloc;
				this->_tree = _treeAlloc.allocate(1);
				_treeAlloc.construct(this->_tree, *(x._tree));
			}

			virtual ~set()
			{
				AlTree _treeAlloc;
				_treeAlloc.destroy(this->_tree);
				_treeAlloc.deallocate(this->_tree, 1);
			}

			set& operator= (const set& x)
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

			pair<iterator,bool> insert (const value_type& val)
			{
				pair<TreeNode*, bool> result = this->_tree->insert(val);
				
				if (result.second == true)
				{
					++this->_size;
					return (pair<iterator,bool>(iterator(result.first), true));
				}
				else
					return (pair<iterator,bool>(iterator(result.first), false));
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
				this->_tree->erase(const_cast<TreeNode*>(position._ptr));
				--this->_size;
			}

			size_type erase (const value_type& val)
			{
				int erase_size = this->_tree->erase(val);
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

			void swap (set& x)
			{
				char buf[sizeof(set)];
				memcpy(buf, reinterpret_cast<void *>(&x), sizeof(set));
				memcpy(reinterpret_cast<char *>(&x), reinterpret_cast<void *>(this), sizeof(set));
				memcpy(reinterpret_cast<char *>(this), reinterpret_cast<void *>(buf), sizeof(set));
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

			iterator find (const value_type& val)
			{
				return (iterator(this->_tree->find(val), this->_tree) );
			}

			const_iterator find (const value_type& val) const
			{
				return (const_iterator(this->_tree->find(val), this->_tree) );
			}

			size_type count (const value_type& val) const
			{
				if (this->find(val) == this->end())
					return (0);
				return (1);
			}

			iterator lower_bound (const value_type& val)
			{
				return (iterator(this->_tree->lowerBound(this->_tree->_root, val, this->_tree->_leaf)));
			}

			const_iterator lower_bound (const value_type& val) const
			{
				return (const_iterator(this->_tree->lowerBound(this->_tree->_root, val, this->_tree->_leaf)));
			}

			iterator upper_bound (const value_type& val)
			{
				return (iterator(this->_tree->upperBound(this->_tree->_root, val, this->_tree->_leaf)));
			}

			const_iterator upper_bound (const value_type& val) const
			{
				return (const_iterator(this->_tree->upperBound(this->_tree->_root, val, this->_tree->_leaf)));
			}

			pair<iterator,iterator> equal_range (const value_type& val)
			{
				return pair<iterator, iterator>(this->lower_bound(val), this->upper_bound(val));
			}

			pair<const_iterator,const_iterator> equal_range (const value_type& val) const
			{
				return pair<const_iterator, const_iterator>(this->lower_bound(val), this->upper_bound(val));
			}

			allocator_type get_allocator() const
			{
				return (this->_alloc);
			}
	};

	template <class T, class Compare, class Alloc>
	bool operator== ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Compare, class Alloc>
	bool operator!= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator<  ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Compare, class Alloc>
	bool operator<= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return ((lhs == rhs) || (lhs < rhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator>  ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return (!(lhs <= rhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator>= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return ((lhs == rhs) || (lhs > rhs));
	}

	template <class T, class Compare, class Alloc>
	void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y)
	{
		x.swap(y);
	}

}

#endif