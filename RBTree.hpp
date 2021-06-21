#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include "utils.hpp"

# define RED true
# define BLACK false

namespace ft
{
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
			};

			typedef typename Alloc::template rebind<TreeNode>::other Alnod;

		private:
			value_compare _comp;
			Alnod _nodeAlloc;
			const bool _isMulti;

			TreeNode* grandParent(TreeNode* node)
			{
				if ((node != NULL) && (node->_parent != NULL))
					return (node->_parent->_parent);
				else
					return (NULL);
			}

			TreeNode* uncle(TreeNode* node)
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
				// 두 노드의 부모의 자식 포인터 변경
				TreeNode temp_a = *a;
				TreeNode temp_b = *b;

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
				if (temp_a._left != this->_leaf)
					temp_a._left->_parent = b;
				if (temp_a._right != this->_leaf)
					temp_a._right->_parent = b;
				if (temp_b._left != this->_leaf)
					temp_b._left->_parent = a;
				if (temp_b._right != this->_leaf)
					temp_b._right->_parent = a;

				char buf[sizeof(TreeNode)];
				memcpy(buf, a, sizeof(TreeNode));
				memcpy(a, b, sizeof(TreeNode)); // 포인터 뿐만 아니라 color도 바꿔주어야 RB 속성 유지 가능
				memcpy(b, buf, sizeof(TreeNode)); // 값만 바꾸는 흉내를 낸다고 생각하면 편함
				a->_value = temp_a._value;
				b->_value = temp_b._value;
			}

			TreeNode* sibling(TreeNode* node)
			{
				if (node == node->_parent->_left)
					return node->_parent->_right;
				else
					return node->_parent->_left;
			}

			bool _isNodeParentLeft(TreeNode* node)
			{
				if (node->_parent->_left == node)
					return (true);
				else
					return (false);
			}

			TreeNode* _getMaxNode(TreeNode* root) // 반복문
			{
				TreeNode* curr = root;
				if (root == this->_leaf)
					return (NULL);
				while (1)
				{
					if (curr->_right == this->_leaf)
						return (curr);
					curr = curr->_right;
				}
				return (NULL);
			}

			TreeNode* _getMinNode(TreeNode* root) // 반복문
			{
				TreeNode* curr = root;
				if (root == this->_leaf)
					return (NULL);
				while (1)
				{
					if (curr->_left == this->_leaf)
						return (curr);
					curr = curr->_left;
				}
				return (NULL);
			}



		public:
			TreeNode* _root;
			TreeNode* _leaf;

			RBTree(const value_compare& comp, bool isMulti = false) : _comp(comp), _isMulti(isMulti);
			{
				this->_leaf = this->_nodeAlloc.allocate(1);
				this->_nodeAlloc.construct(this->_leaf, TreeNode());
				this->_leaf->_color = BLACK;
				this->_root = this->_leaf;
			}

			TreeNode* find(const value_type& value) const
			{
				TreeNode* curr = this->_root;

				if (this->_root == this->_leaf) // isEmpty
					return (NULL);

				while (1)
				{
					if (curr == this->_leaf) // leaf이면 못찾음
						return (NULL);

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

				// return (this->_find(this->_root, value));
			}

			// TreeNode* find(TreeNode* node, const value_type& value) const
			// {
				
			// }


			TreeNode* insert(const value_type& value)
			{
				TreeNode* newNode = this->_nodeAlloc.allocate(1);
				this->_nodeAlloc.construct(newNode, TreeNode());
				newNode->_value = value;
				newNode->_color = RED; // 삽입하는 노드는 항상 적색이다
				newNode->_left = this->_leaf;
				newNode->_right = this->_leaf;


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
						curr = curr->_right;
				}

				newNode->_parent = parent;

				if (parent == NULL) // 비어있는 트리에 삽입한 경우 루트 변경
					this->_root = newNode;
				else if (_comp(newNode->_value, parent->_value)) // 부모에 자식 연결시켜주기
					parent->_left = newNode;
				else
					parent->_right = newNode; // 작은 경우 외(같거나 큰 경우)에는 모두 오른쪽 자식

				this->_insertFixUp(newNode);
				return (newNode);
			}

			void erase(const value_type& value)
			{
				TreeNode* toDelete;
				while (1)
				{
					toDelete = this->find(value);
					if (toDelete == NULL)
						return ;

					// std::cout << key << std::endl;
					// this->show_tree(this->_root, "", true);
					this->_deleteNode(toDelete);
				}
			}

			TreeNode* getNextNode(TreeNode* node) const
			{
				if (node == this->_leaf)
					return (this->_getMinNode(this->_root));
				if (node->_right != this->_leaf)
					return (this->_getMinNode(node->_right));

				TreeNode* curr = node;
				while (1)
				{
					if (curr->_parent == NULL)
						return (this->_leaf);
					if (this->_isNodeParentLeft(curr))
						return (node->_parent);
					else
						curr = curr->_parent;
				}
				return (NULL);
			}

			TreeNode* getPrevNode(TreeNode* node) const
			{
				if (node == this->_leaf)
					return (this->_getMaxNode(this->_root));
				if (node->_left != this->_leaf)
					return (this->_getMaxNode(node->_left));
				
				TreeNode* curr = node;
				while (1)
				{
					if (curr->_parent == NULL)
						return (this->_leaf);
					if (!this->_isNodeParentLeft(curr))
						return (node->_parent);
					else
						curr = curr->_parent;
				}
			}

	


	
	
			// /*show tree*/
			// void show_tree(TreeNode* root, std::string indent, bool last)
			// {
			// // print the tree structure on the screen
			// if (root != this->_leaf)
			// {
			// std::cout << indent;
			// if (last)
			// {
			// std::cout << "R----";
			// indent += "     ";
			// }
			// else
			// {
			// std::cout << "L----";
			// indent += "|    ";
			// }

			// std::string sColor = (root->_color == RED) ? "RED" : "BLACK";
			// std::cout << root->_key << "(" << sColor << ")" << std::endl;
			// show_tree(root->_left, indent, false);
			// show_tree(root->_right, indent, true);
			// }
			// }

			// void printInorder(TreeNode* root)
			// {
			// if (root == this->_leaf)
			// return ;
			// this->printInorder(root->_left);
			// this->vector.push_back(root->_key);
			// std::cout << root->_key << " ";
			// this->printInorder(root->_right);
			// }

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
					TreeNode *switch_child = this->_getMaxNode(toDelete->_left); // 왼쪽 서브트리의 최댓값 찾기
					this->_swapNode(toDelete, switch_child);
					this->_deleteNode(toDelete);
				}
				// 오른쪽 서브트리만 가지는 경우
				else if (toDelete->_left == this->_leaf && toDelete->_right != this->_leaf)
				{
					TreeNode *switch_child = this->_getMinNode(toDelete->_right); // 왼쪽 서브트리의 최댓값 찾기
					this->_swapNode(toDelete, switch_child);
					this->_deleteNode(toDelete);
				}
				// 오른쪽 왼쪽 서브트리 모두 가질 경우
				// 왼쪽 서브트리의 가장 큰 값 또는 오른쪽 가장 작은 값을 가진 노드를 연결한다
				else // 왼쪽 서브트리의 가장 큰 값을 기본으로 선택하도록 만들었다
				{
					TreeNode *switch_child;
					if (toDelete->_left != this->_leaf) // 바꿔줄 최소 or 최대 노드 선택
						switch_child = this->_getMaxNode(toDelete->_left);
					else
						switch_child = this->_getMinNode(toDelete->_right);

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
			const RBTree<T, Compare>* _rbtree;

		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef ft::bidirectional_iterator_tag iterator_category;
			typedef typename choose<IsConst, const T &, T &>::type reference;
			typedef typename choose<IsConst, const T *, T *>::type pointer;	
			
			Node _ptr;

			// commmon
			RBTreeIterator(Node ptr = NULL, RBTree<T, Compare>* rbtree = NULL) : _ptr(ptr), _rbtree(rbtree) {}

			RBTreeIterator(const RBTreeIterator<T, Compare, false>& ref) : _ptr(ref._ptr), _rbtree(ref._rbtree) {}
			
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