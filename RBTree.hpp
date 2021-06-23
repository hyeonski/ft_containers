#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include "utils.hpp"

# define RED true
# define BLACK false

namespace ft
{
	template <class T, class Compare, bool IsConst>
	class RBTreeIterator;

	template <class T, class Compare, class Alloc = std::allocator<T> >
	class RBTree
	{
		public:
			typedef T value_type;
			typedef Compare value_compare;
			typedef RBTreeIterator<T, Compare, false> iterator;
			typedef RBTreeIterator<T, Compare, true> const_iterator;

			struct TreeNode
			{
				T _value;
				TreeNode* _parent;
				TreeNode* _left;
				TreeNode* _right;
				bool _color;

				TreeNode() : _parent(NULL), _left(NULL), _right(NULL), _color(RED) {}
				TreeNode(T value) : _value(value), _parent(NULL), _left(NULL), _right(NULL), _color(RED) {}
			};

			typedef typename Alloc::template rebind<TreeNode>::other Alnod;

		private:
			value_compare _comp;
			const bool _isMulti;

			TreeNode* grandParent(TreeNode* node) const
			{
				if ((node != NULL) && (node->_parent != NULL))
					return (node->_parent->_parent);
				else
					return (NULL);
			}

			TreeNode* uncle(TreeNode* node) const
			{
				TreeNode* grandParent = this->grandParent(node);
				if (grandParent == NULL)
					return (NULL);
				if (node->_parent == grandParent->_left)
					return (grandParent->_right);
				else
					return (grandParent->_left);
			}

			void rotate_left(TreeNode* node)
			{
				TreeNode* rightChild = node->_right;
				TreeNode* parent = node->_parent;

				if (rightChild->_left != this->_leaf)
					rightChild->_left->_parent = node;

				node->_right = rightChild->_left;
				node->_parent = rightChild;
				rightChild->_left = node;
				rightChild->_parent = parent;

				if (parent != NULL)
				{
					if (parent->_left == node)
						parent->_left = rightChild;
					else
						parent->_right = rightChild;
				}
				else
					this->_root = rightChild;
			}

			void rotate_right(TreeNode* node)
			{
				TreeNode* leftChild = node->_left;
				TreeNode* parent = node->_parent;

				if (leftChild->_right != this->_leaf)
					leftChild->_right->_parent = node;

				node->_left = leftChild->_right;
				node->_parent = leftChild;
				leftChild->_right = node;
				leftChild->_parent = parent;

				if (parent != NULL)
				{
					if (parent->_right == node)
						parent->_right = leftChild;
					else
						parent->_left = leftChild;
				}
				else
					this->_root = leftChild;
			}

			void _swapNode(TreeNode* a, TreeNode* b)
			{
				if (a->_parent != NULL && a->_parent == b)
					this->_swapParentChild(b, a);
				else if (b->_parent != NULL && b->_parent == a)
					this->_swapParentChild(a, b);
				else
				{
					TreeNode* aParent = a->_parent;
					TreeNode* aLeft = a->_left;
					TreeNode* aRight = a->_right;
					bool aColor = a->_color;

					TreeNode* bParent = b->_parent;
					TreeNode* bLeft = b->_left;
					TreeNode* bRight = b->_right;
					bool bColor = b->_color;

					// 두 노드의 부모의 자식 포인터 변경
					if (a->_parent != NULL)
					{
						if (this->_isNodeParentLeft(a))
							a->_parent->_left = b;
						else
							a->_parent->_right = b;
					}
					else
						this->_root = b;
					if (b->_parent != NULL)
					{
						if (this->_isNodeParentLeft(b))
							b->_parent->_left = a;
						else
							b->_parent->_right = a;
					}
					else
						this->_root = a;

					// 두 노드 자식들의 부모 포인터 변경
					if (aLeft != this->_leaf)
						aLeft->_parent = b;
					if (aRight != this->_leaf)
						aRight->_parent = b;

					if (bLeft != this->_leaf)
						bLeft->_parent = a;
					if (bRight != this->_leaf)
						bRight->_parent = a;

					a->_parent = bParent;
					a->_left = bLeft;
					a->_right = bRight;
					a->_color = bColor;

					b->_parent = aParent;
					b->_left = aLeft;
					b->_right = aRight;
					b->_color = aColor;
				}
			}

			void _swapParentChild(TreeNode* parent, TreeNode* child)
			{
				TreeNode* pParent = parent->_parent;
				TreeNode* pLeft = parent->_left;
				TreeNode* pRight = parent->_right;
				bool pColor = parent->_color;

				TreeNode* cLeft = child->_left;
				TreeNode* cRight = child->_right;
				bool cColor = child->_color;

				if (parent->_parent != NULL)
				{
					if (this->_isNodeParentLeft(parent))
						pParent->_left = child;
					else
						pParent->_right = child;
				}
				else
					this->_root = child;
				
				if (cLeft != this->_leaf)
					cLeft->_parent = parent;
				if (cRight != this->_leaf)
					cRight->_parent = parent;

				parent->_parent = child;
				parent->_color = cColor;
				child->_color = pColor;
				if (child == parent->_left)
				{
					parent->_left = cLeft;
					parent->_right = cRight;
					child->_parent = pParent;

					pRight->_parent = child;
					child->_left = parent;
					child->_right = pRight;
				}
				else
				{
					parent->_left = cLeft;
					parent->_right = cRight;
					child->_parent = pParent;

					pLeft->_parent = child;
					child->_left = pLeft;
					child->_right = parent;
				}
			}

			TreeNode* sibling(TreeNode* node) const
			{
				if (node == node->_parent->_left)
					return node->_parent->_right;
				else
					return node->_parent->_left;
			}

			bool _isNodeParentLeft(const TreeNode* node) const
			{
				if (node->_parent->_left == node)
					return (true);
				else
					return (false);
			}

		public:
			TreeNode* _root;
			TreeNode* _leaf;
			Alnod _nodeAlloc;

			RBTree(const value_compare& comp, bool isMulti = false) : _comp(comp), _isMulti(isMulti)
			{
				this->_leaf = this->_nodeAlloc.allocate(1);
				this->_nodeAlloc.construct(this->_leaf, TreeNode());
				this->_leaf->_color = BLACK;
				this->_root = this->_leaf;
			}

			RBTree(const RBTree& x) : _comp(x._comp), _isMulti(x._isMulti), _nodeAlloc(x._nodeAlloc)
			{
				this->_leaf = this->_nodeAlloc.allocate(1);
				this->_nodeAlloc.construct(this->_leaf, TreeNode());
				this->_leaf->_color = BLACK;
				this->_root = this->_leaf;

				this->copyTree(x, x._root);
			}

			~RBTree()
			{
				this->clearTree(this->_root);
				this->_nodeAlloc.destroy(this->_leaf);
				this->_nodeAlloc.deallocate(this->_leaf, 1);
			}
			
			RBTree& operator=(const RBTree& x)
			{
				if (this != &x)
				{
					this->clearTree(this->_root);
					this->copyTree(x, x._root);
				}
				return (*this);
			}

			void copyTree(const RBTree& x, TreeNode* node)
			{
				if (node == x._leaf)
					return ;
				this->insert(node->_value);
				this->copyTree(x, node->_left);
				this->copyTree(x, node->_right);
			}

			void clearTree(TreeNode* node)
			{
				if (node == this->_leaf)
					return ;
				this->clearTree(node->_left);
				this->clearTree(node->_right);


				if (node->_parent != NULL)
				{
					if (this->_isNodeParentLeft(node)) // 지우려는 노드가 부모의 왼쪽인지 오른쪽인지 파악하여 link 끊어준다
						node->_parent->_left = this->_leaf;
					else
						node->_parent->_right = this->_leaf;
				}
				else // 루트노드 삭제 시 비어있는 트리
					this->_root = this->_leaf;
				this->_nodeAlloc.destroy(node);
				this->_nodeAlloc.deallocate(node, 1);

			}

			TreeNode* find(const value_type& value) const
			{
				TreeNode* curr = this->_root;

				if (this->_root == this->_leaf) // isEmpty
					return (this->_leaf);

				while (1)
				{
					if (curr == this->_leaf) // leaf이면 못찾음
						return (this->_leaf);

					if (!_comp(value, curr->_value) && !_comp(curr->_value, value)) // 서로 작지 않을 경우에는 같다
					{
						return (curr);
					}
					if (_comp(value, curr->_value)) // 찾고자 하는 value가 노드보다 작으면 왼쪽
						curr = curr->_left;
					else
						curr = curr->_right;
				}
				return (NULL);
			}


			pair<TreeNode*, bool> insert(const value_type& value)
			{
				TreeNode* curr = this->_root;
				TreeNode* parent = NULL;

				while (1)
				{
					if (curr == this->_leaf)
						break ;
					parent = curr;
					if (_comp(value, curr->_value))
						curr = curr->_left;
					else
					{
						if (!_comp(value, curr->_value) && !_comp(curr->_value, value)) // 같을 때
						{
							if (!this->_isMulti) // 멀티 트리가 아니라면
								return (pair<TreeNode*, bool>(curr, false)); // insert하지 않고 현재 노드(같은 값) 리턴
						}
						curr = curr->_right;
					}
				}

				TreeNode* newNode = this->_nodeAlloc.allocate(1);
				this->_nodeAlloc.construct(newNode, TreeNode(value));
				newNode->_color = RED; // 삽입하는 노드는 항상 적색이다
				newNode->_left = this->_leaf;
				newNode->_right = this->_leaf;
				newNode->_parent = parent;

				if (parent == NULL) // 비어있는 트리에 삽입한 경우 루트 변경
					this->_root = newNode;
				else if (_comp(newNode->_value, parent->_value)) // 부모에 자식 연결시켜주기
					parent->_left = newNode;
				else
					parent->_right = newNode; // 작은 경우 외(같거나 큰 경우)에는 모두 오른쪽 자식

				this->_insertFixUp(newNode);
				return (pair<TreeNode*, bool>(newNode, true));
			}

			int erase(const value_type& value)
			{
				TreeNode* toDelete;
				int cnt = 0;
				while (1)
				{
					toDelete = this->find(value);
					if (toDelete == this->_leaf)
						break ;

					this->_deleteNode(toDelete);
					++cnt;
				}
				return (cnt);
			}

			int erase(TreeNode* toDelete)
			{
				this->_deleteNode(toDelete);
				return (1);
			}

			TreeNode* getMaxNode(TreeNode* root) const
			{
				TreeNode* curr = root;
				if (root == this->_leaf)
					return (this->_leaf);
				while (1)
				{
					if (curr->_right == this->_leaf)
						return (curr);
					curr = curr->_right;
				}
				return (NULL);
			}

			TreeNode* getMinNode(TreeNode* root) const
			{
				TreeNode* curr = root;
				if (root == this->_leaf)
					return (this->_leaf);
				while (1)
				{
					if (curr->_left == this->_leaf)
						return (curr);
					curr = curr->_left;
				}
				return (NULL);
			}

			TreeNode* getNextNode(const TreeNode* node) const
			{
				if (node == this->_leaf)
					return (this->getMinNode(this->_root));
				if (node->_right != this->_leaf)
					return (this->getMinNode(node->_right));

				const TreeNode* curr = node;
				while (1)
				{
					if (curr->_parent == NULL)
						return (this->_leaf);
					if (this->_isNodeParentLeft(curr))
						return (curr->_parent);
					else
						curr = curr->_parent;
				}
				return (NULL);
			}

			TreeNode* getPrevNode(const TreeNode* node) const
			{
				if (node == this->_leaf)
					return (this->getMaxNode(this->_root));
				if (node->_left != this->_leaf)
					return (this->getMaxNode(node->_left));
				
				const TreeNode* curr = node;
				while (1)
				{
					if (curr->_parent == NULL)
						return (this->_leaf);
					if (!this->_isNodeParentLeft(curr))
						return (curr->_parent);
					else
						curr = curr->_parent;
				}
			}

			TreeNode* lowerBound(TreeNode* begin, const value_type& value, TreeNode* end) const
			{
				TreeNode* curr = begin;

				if (_comp(this->getMaxNode(this->_root)->_value, value))
					return (end);
				while (1)
				{
					if (curr == end)
						return (end);
					if (!_comp(curr->_value, value) && !_comp(value, curr->_value)) // 같으면
						return (curr);
					else if (_comp(curr->_value, value))
					{
						if (curr->_right == end)
							return (this->getNextNode(curr));
						curr = curr->_right;
					}
					else
					{
						if (curr->_left == end)
							return (curr);
						curr = curr->_left;
					}
				}
			}

			TreeNode* upperBound(TreeNode* begin, const value_type& value, TreeNode* end) const
			{
				TreeNode* curr = begin;
				if (!_comp(value, this->getMaxNode(this->_root)->_value))
					return (end);
				while (1)
				{
					if (curr == end)
						return (end);
					else if (!_comp(value, curr->_value))
					{
						if (curr->_right == end)
							return (this->getNextNode(curr));
						curr = curr->_right;
					}
					else
					{
						if (curr->_left == end)
							return (curr);
						curr = curr->_left;
					}
				}
			}

			/*show tree*/
			void show_tree(TreeNode* root, std::string indent, bool last) const
			{
			// print the tree structure on the screen
			if (root != this->_leaf)
			{
			std::cout << indent;
			if (last)
			{
			std::cout << "R----";
			indent += "     ";
			}
			else
			{
			std::cout << "L----";
			indent += "|    ";
			}

			std::string sColor = (root->_color == RED) ? "RED" : "BLACK";
			std::cout << root->_value.first << "(" << sColor << ")" << std::endl;
			show_tree(root->_left, indent, false);
			show_tree(root->_right, indent, true);
			}
			}

			void printInorder(TreeNode* root) const
			{
				if (root == this->_leaf)
					return ;
				this->printInorder(root->_left);
				std::cout << root->_value.first << std::endl;
				std::cout << root->_value.second << std::endl;
				this->printInorder(root->_right);
			}

			// void check_traversal()
			// {
			// TreeNode* curr = this->_root;
			// TreeNode* prev = NULL;
			// while (1)
			// {
			// // std::cout << curr->_key << std::endl;
			// this->vector.push_back(curr->_key);
			// if (prev == curr->_right)
			// {
			// prev = curr;
			// if (curr->_parent != NULL)
			// curr = curr->_parent;
			// else
			// return ;
			// continue ;
			// }
			// else if (prev == curr->_left)
			// {
			// prev = curr;
			// if (curr->_right == this->_leaf)
			// curr = curr->_parent;
			// else
			// curr = curr->_right;
			// continue ;
			// }

			// if (curr->_left != this->_leaf)
			// {
			// prev = curr;
			// curr = curr->_left;
			// continue ;	
			// }
			// if (curr->_right != this->_leaf)
			// {
			// prev = curr;
			// curr = curr->_right;
			// continue ;
			// }
			// prev = curr;
			// curr = curr->_parent;
			// continue ;
			// }
			// }
		private:
			void _insertFixUp(TreeNode* newNode)
			{
				this->_insert_case1(newNode);
			}

			void _insert_case1(TreeNode* node)
			{
				if (node->_parent == NULL) // 삽입한 노드가 루트일 경우 흑색으로 변경 후 종료 - case1
				{
					node->_color = BLACK;
					return ;
				}
				else
					this->_insert_case2(node);
			}

			void _insert_case2(TreeNode* node)
			{
				if (node->_parent->_color == BLACK) // 삽입 노드의 부모가 black인 경우 - case2
					return ; // 트리 재조정 없이 붙여주고 바로 종료
				else
					this->_insert_case3(node);
			}

			void _insert_case3(TreeNode* node)
			{
				TreeNode* uncle = this->uncle(node);
				TreeNode* grandParent;

				if (uncle != NULL && uncle->_color == RED) // uncle이 red면 recolor
				{
					node->_parent->_color = BLACK;
					uncle->_color = BLACK;
					grandParent = this->grandParent(node);
					grandParent->_color = RED;
					this->_insert_case1(grandParent);
				}
				else
					this->_insert_case4(node);
			}

			void _insert_case4(TreeNode* node) // uncle이 black인 경우
			{
				TreeNode* grandParent = this->grandParent(node);

				if ((node == node->_parent->_right) && (node->_parent == grandParent->_left)) // 노드가 부모의 오른쪽 자식이고, 부모는 조부모의 왼쪽 자식이다
				{
					this->rotate_left(node->_parent); // 부모를 중심으로 왼쪽으로 회전
					node = node->_left; // 회전 시 자식이 올라오므로 부모였던 노드로 내려간다
				}
				else if ((node == node->_parent->_left) && (node->_parent == grandParent->_right))
				{
					this->rotate_right(node->_parent); // 부모를 중심으로 오른쪽으로 회전
					node = node->_right;
				}
				this->_insert_case5(node); // 부모였던 노드 (회전 시 자식으로 내려간 노드)를 기준으로 case5 재조정 실행
			}

			void _insert_case5(TreeNode* node)
			{
				TreeNode* grandParent = this->grandParent(node);

				node->_parent->_color = BLACK;
				grandParent->_color = RED;
				if (node == node->_parent->_left)
				{
					if (grandParent == this->_root)
						this->_root = grandParent->_left;
					this->rotate_right(grandParent);
				}
				else
				{
					if (grandParent == this->_root)
						this->_root = grandParent->_right;
					this->rotate_left(grandParent);
				}
			}

			void _deleteNode(TreeNode* toDelete)
			{
				TreeNode* parent = toDelete->_parent;

				// 삭제하려는 노드의 자식노드가 없는 경우
				if (toDelete->_left == this->_leaf && toDelete->_right == this->_leaf)
				{
					this->_deleteFixUp(toDelete);
					if (parent != NULL)
					{
						if (this->_isNodeParentLeft(toDelete)) // 지우려는 노드가 부모의 왼쪽인지 오른쪽인지 파악하여 link 끊어준다
							parent->_left = this->_leaf;
						else
							parent->_right = this->_leaf;
					}
					else // 루트노드 삭제 시 비어있는 트리
						this->_root = this->_leaf;
					this->_nodeAlloc.destroy(toDelete);
					this->_nodeAlloc.deallocate(toDelete, 1);
				}
				// 왼쪽 서브트리만 가지는 경우
				else if (toDelete->_left != this->_leaf && toDelete->_right == this->_leaf)
				{
					TreeNode *switch_child = this->getMaxNode(toDelete->_left); // 왼쪽 서브트리의 최댓값 찾기
					this->_swapNode(toDelete, switch_child);
					this->_deleteNode(toDelete);
				}
				// 오른쪽 서브트리만 가지는 경우
				else if (toDelete->_left == this->_leaf && toDelete->_right != this->_leaf)
				{
					TreeNode *switch_child = this->getMinNode(toDelete->_right); // 왼쪽 서브트리의 최댓값 찾기
					this->_swapNode(toDelete, switch_child);
					this->_deleteNode(toDelete);
				}
				// 오른쪽 왼쪽 서브트리 모두 가질 경우
				// 왼쪽 서브트리의 가장 큰 값 또는 오른쪽 가장 작은 값을 가진 노드를 연결한다
				else // 왼쪽 서브트리의 가장 큰 값을 기본으로 선택하도록 만들었다
				{
					TreeNode *switch_child;
					if (toDelete->_left != this->_leaf) // 바꿔줄 최소 or 최대 노드 선택
						switch_child = this->getMaxNode(toDelete->_left);
					else
						switch_child = this->getMinNode(toDelete->_right);

					this->_swapNode(toDelete, switch_child); // 선택된 단말 노드와 위치 바꿈
					this->_deleteNode(toDelete);
				}
			}

			void _deleteFixUp(TreeNode* node)
			{
				if (node->_color == RED) // red 삭제 시 종료
					return ;
				this->_delete_case1(node);
			}

			void _delete_case1(TreeNode* node)
			{
				if (node->_parent == NULL) // root 삭제 시 종료
					return ;
				this->_delete_case2(node);
			}

			void _delete_case2(TreeNode* node) // double black의 형제가 red일 경우
			{
				TreeNode* sibling = this->sibling(node);

				if (sibling->_color == RED)
				{
					node->_parent->_color = RED; // parent와 sibling color swap
					sibling->_color = BLACK; // sibling이 red이므로 부모는 무조건 black, 즉 색을 정해주기만 해도 된다
					if (this->_isNodeParentLeft(node))
						this->rotate_left(node->_parent);
					else
						this->rotate_right(node->_parent);
				}
				this->_delete_case3(node);
			}

			void _delete_case3(TreeNode* node)
			{
				TreeNode* sibling = this->sibling(node);

				if ((node->_parent->_color == BLACK)
					&& (sibling->_color == BLACK)
					&& (sibling->_left->_color == BLACK)
					&& (sibling->_right->_color == BLACK))
				{
					sibling->_color = RED;
					this->_delete_case1(node->_parent);
				}
				else
					this->_delete_case4(node);
			}

			void _delete_case4(TreeNode* node)
			{
				TreeNode* sibling = this->sibling(node);

				if ((node->_parent->_color == RED)
					&& (sibling->_color == BLACK)
					&& (sibling->_left->_color == BLACK)
					&& (sibling->_right->_color == BLACK))
				{
					sibling->_color = RED;
					node->_parent->_color = BLACK;
				}
				else
					this->_delete_case5(node);
			}

			void _delete_case5(TreeNode* node)
			{
				TreeNode* sibling = this->sibling(node);

				if (sibling->_color == BLACK)
				{
					if ((node == node->_parent->_left)
						&& (sibling->_right->_color == BLACK)
						&& (sibling->_left->_color == RED))
					{
						sibling->_color = RED;
						sibling->_left->_color = BLACK;
						this->rotate_right(sibling);
					}
					else if ((node == node->_parent->_right)
						&& (sibling->_left->_color == BLACK)
						&& (sibling->_right->_color == RED))
					{
						sibling->_color = RED;
						sibling->_right->_color = BLACK;
						this->rotate_left(sibling);
					}
				}
				this->_delete_case6(node);
			}

			void _delete_case6(TreeNode* node)
			{
				TreeNode* sibling = this->sibling(node);

				sibling->_color = node->_parent->_color; // 부모-형제 color swap
				node->_parent->_color = BLACK;

				if (node == node->_parent->_left)
				{
					sibling->_right->_color = BLACK;
					this->rotate_left(node->_parent);
				}
				else
				{
					sibling->_left->_color = BLACK;
					this->rotate_right(node->_parent);
				}
			}
	};

	template <class T, class Compare, bool IsConst>
	class RBTreeIterator
	{
		private:
			typedef typename choose<IsConst, const typename RBTree<T, Compare>::TreeNode *, typename RBTree<T, Compare>::TreeNode * >::type Node;

		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef ft::bidirectional_iterator_tag iterator_category;
			typedef typename choose<IsConst, const T &, T &>::type reference;
			typedef typename choose<IsConst, const T *, T *>::type pointer;	
			
			const RBTree<T, Compare>* _rbtree;
			Node _ptr;

			// commmon
			RBTreeIterator(Node ptr = NULL, RBTree<T, Compare>* rbtree = NULL) : _rbtree(rbtree), _ptr(ptr) {}

			RBTreeIterator(const RBTreeIterator<T, Compare, false>& ref) : _rbtree(ref._rbtree), _ptr(ref._ptr) {}
			
			RBTreeIterator& operator=(const RBTreeIterator& ref)
			{
				if (this != &ref)
				{
					this->_ptr = ref._ptr;
					this->_rbtree = ref._rbtree;
				}
				return (*this);
			}

			virtual ~RBTreeIterator() {}
			
			RBTreeIterator& operator++()
			{
				this->_ptr = this->_rbtree->getNextNode(this->_ptr);
				return (*this);
			}

			RBTreeIterator operator++(int)
			{
				RBTreeIterator temp(*this);

				this->_ptr = this->_rbtree->getNextNode(this->_ptr);
				return (temp);
			}

			// input
			bool operator==(const RBTreeIterator<T, Compare, true>& iter) const
			{
				return (this->_ptr == iter._ptr);
			}

			bool operator==(const RBTreeIterator<T, Compare, false>& iter) const
			{
				return (this->_ptr == iter._ptr);
			}

			bool operator!=(const RBTreeIterator<T, Compare, true>& iter) const
			{
				return (this->_ptr != iter._ptr);
			}

			bool operator!=(const RBTreeIterator<T, Compare, false>& iter) const
			{
				return (this->_ptr != iter._ptr);
			}

			reference operator*() const
			{
				return (this->_ptr->_value);
			}

			pointer operator->() const
			{
				return (&(this->_ptr->_value));
			}

			// output

			// forward

			// bidirectional
			RBTreeIterator& operator--()
			{
				this->_ptr = this->_rbtree->getPrevNode(this->_ptr);
				return (*this);
			}

			RBTreeIterator operator--(int)
			{
				RBTreeIterator temp(*this);

				this->_ptr = this->_rbtree->getPrevNode(this->_ptr);
				return (temp);
			}
	};

}


#endif
