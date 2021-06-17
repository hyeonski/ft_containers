#include <iostream>
#include <vector>

#define RED true
#define BLACK false

struct TreeNode
{
	int _key;
	TreeNode* _left;
	TreeNode* _right;
	TreeNode* _parent;
	bool _color;

	TreeNode() : _key(0), _left(NULL), _right(NULL), _parent(NULL), _color(BLACK) {}
};

class RBTree
{
	public:
		TreeNode* _root;
		TreeNode* _leaf;
		std::vector<int> vector;

		RBTree()
		{
			this->_leaf = new TreeNode();
			this->_leaf->_color = BLACK;
			this->_root = this->_leaf;
		}

		TreeNode* findKey(int key)
		{
			TreeNode* curr = this->_root;

			if (this->_root == this->_leaf) // isEmpty
				return (NULL);

			while (1)
			{
				if (curr == this->_leaf)
					return (NULL);
				if (curr->_key == key)
					return (curr);
				if (curr->_key > key)
					curr = curr->_left;
				else
					curr = curr->_right;
			}
			return (NULL);
		}

		TreeNode* insertKey(int key)
		{
			TreeNode* newNode = new TreeNode();
			newNode->_key = key;
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
				if (curr->_key == key)
					return (NULL);
				if (curr->_key > key)
					curr = curr->_left;
				else
					curr = curr->_right;
			}

			newNode->_parent = parent;

			if (parent == NULL) // 비어있는 트리에 삽입한 경우 루트 변경
				this->_root = newNode;
			else if (parent->_key > newNode->_key) // 부모에 자식 연결시켜주기
				parent->_left = newNode;
			else
				parent->_right = newNode;

			this->_insertFixUp(newNode);
			return (newNode);
		}

		void deleteKey(int key)
		{
			TreeNode* toDelete = this->findKey(key);
			if (toDelete == NULL)
				return ;

			this->_deleteNode(toDelete);
		}

		void _deleteNode(TreeNode* toDelete)
		{
			TreeNode* parent = toDelete->_parent;

			// 삭제하려는 노드의 자식노드가 없는 경우
			if (toDelete->_left == this->_leaf && toDelete->_right == this->_leaf)
			{
				if (parent != NULL)
				{
					if (this->_isNodeParentLeft(toDelete)) // 지우려는 노드가 부모의 왼쪽인지 오른쪽인지 파악하여 link 끊어준다
						parent->_left = this->_leaf;
					else
						parent->_right = this->_leaf;
				}
				else // 루트노드 삭제 시 비어있는 트리
					this->_root = this->_leaf;
				delete toDelete;
			}
			// 왼쪽 서브트리만 가지는 경우
			else if (toDelete->_left != this->_leaf && toDelete->_right == this->_leaf)
			{
				if (parent != NULL)
				{
					TreeNode* subTree = toDelete->_left;
					if (this->_isNodeParentLeft(toDelete))
						parent->_left = subTree;
					else
						parent->_right = subTree;
				}
				else
					toDelete->_left->_parent = NULL; // 루트 노드 삭제 시 서브트리의 루트를 전체 루트로 만든다
				delete toDelete;
			}
			// 오른쪽 서브트리만 가지는 경우
			else if (toDelete->_left == this->_leaf && toDelete->_right != this->_leaf)
			{
				TreeNode* subTree = toDelete->_right;
				if (parent != NULL)
				{
					if (this->_isNodeParentLeft(toDelete))
						parent->_left = subTree;
					else
						parent->_right = subTree;
				}
				else
					toDelete->_right->_parent = NULL;
				delete toDelete;
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

		virtual void _swapNode(TreeNode* a, TreeNode* b)
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
			if (b->_parent != NULL)
			{
				if (this->_isNodeParentLeft(b))
					b->_parent->_left = a;
				else
					b->_parent->_right = a;
			}

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
			memcpy(a, b, sizeof(TreeNode));
			memcpy(b, buf, sizeof(TreeNode));
		}

		virtual bool _isNodeParentLeft(TreeNode* node)
		{
			if (node->_parent->_left == node)
				return (true);
			else
				return (false);
		}

		virtual TreeNode* _getMaxNode(TreeNode* root) // 반복문
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

		virtual TreeNode* _getMinNode(TreeNode* root) // 반복문
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
		}

		/*show tree*/
		void show_tree(TreeNode* root, std::string indent, bool last)
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
				std::cout << root->_key << "(" << sColor << ")" << std::endl;
				show_tree(root->_left, indent, false);
				show_tree(root->_right, indent, true);
			}
		}

		void printInorder(TreeNode* root)
		{
			if (root == this->_leaf)
				return ;
			this->printInorder(root->_left);
			std::cout << root->_key << " ";
			this->printInorder(root->_right);
		}

		void check_traversal()
		{
			TreeNode* curr = this->_root;
			TreeNode* prev = NULL;
			while (1)
			{
				// std::cout << curr->_key << std::endl;
				this->vector.push_back(curr->_key);
				if (prev == curr->_right)
				{
					prev = curr;
					if (curr->_parent != NULL)
						curr = curr->_parent;
					else
						return ;
					continue ;
				}
				else if (prev == curr->_left)
				{
					prev = curr;
					if (curr->_right == this->_leaf)
						curr = curr->_parent;
					else
						curr = curr->_right;
					continue ;
				}

				if (curr->_left != this->_leaf)
				{
					prev = curr;
					curr = curr->_left;
					continue ;	
				}
				if (curr->_right != this->_leaf)
				{
					prev = curr;
					curr = curr->_right;
					continue ;
				}
				prev = curr;
				curr = curr->_parent;
				continue ;
			}
		}
};


int main()
{
	RBTree tree;

	for (int i = 0; i < 100; ++i)
		tree.insertKey(rand() % 100);
	tree.printInorder(tree._root);
	std::cout << std::endl;

	// for (int i = 0; i < 100; ++i)
	// 	tree.deleteKey(i);
	tree.show_tree(tree._root, "", true);

	tree.deleteKey(7);

	// tree.show_tree(tree._root, "", true);
	tree.printInorder(tree._root);
	std::cout << std::endl;
	// tree.check_traversal();
	// std::sort(tree.vector.begin(), tree.vector.end());
	// for (std::vector<int>::iterator iter = tree.vector.begin(); iter != tree.vector.end(); iter++)
	// 	std::cout << *iter << " ";
	// std::cout << std::endl;
}


// R----49(BLACK)
//      L----27(BLACK)
//      |    L----9(RED)
//      |    |    L----3(BLACK)
//      |    |    |    L----1(BLACK)
//      |    |    |    R----7(RED)
//      |    |    |         L----5(BLACK)
//      |    |    |         |    L----4(RED)
//      |    |    |         R----8(BLACK)
//      |    |    R----16(BLACK)
//      |    |         L----12(RED)
//      |    |         |    L----10(BLACK)
//      |    |         |    R----14(BLACK)
//      |    |         |         L----13(RED)
//      |    |         |         R----15(RED)
//      |    |         R----23(RED)
//      |    |              L----21(BLACK)
//      |    |              |    L----17(RED)
//      |    |              |    R----22(RED)
//      |    |              R----25(BLACK)
//      |    |                   L----24(RED)
//      |    |                   R----26(RED)
//      |    R----35(RED)
//      |         L----30(BLACK)
//      |         |    L----29(BLACK)
//      |         |    |    L----28(RED)
//      |         |    R----33(BLACK)
//      |         R----42(BLACK)
//      |              L----37(RED)
//      |              |    L----36(BLACK)
//      |              |    R----40(BLACK)
//      |              |         L----38(RED)
//      |              R----44(BLACK)
//      |                   R----45(RED)
//      R----85(RED)
//           L----72(BLACK)
//           |    L----65(RED)
//           |    |    L----58(BLACK)
//           |    |    |    L----53(RED)
//           |    |    |    |    L----51(BLACK)
//           |    |    |    |    |    R----52(RED)
//           |    |    |    |    R----57(BLACK)
//           |    |    |    R----60(BLACK)
//           |    |    |         R----63(RED)
//           |    |    R----68(BLACK)
//           |    |         L----67(BLACK)
//           |    |         |    L----66(RED)
//           |    |         R----69(BLACK)
//           |    R----78(BLACK)
//           |         L----73(BLACK)
//           |         |    R----77(RED)
//           |         R----81(BLACK)
//           |              L----79(RED)
//           |              R----82(RED)
//           R----94(BLACK)
//                L----92(BLACK)
//                |    L----90(RED)
//                |    |    L----87(BLACK)
//                |    |    |    R----88(RED)
//                |    |    R----91(BLACK)
//                |    R----93(BLACK)
//                R----97(BLACK)
//                     L----96(BLACK)
//                     |    L----95(RED)
//                     R----99(BLACK)
//                          L----98(RED)