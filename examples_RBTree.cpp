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
			// std::cout << key << std::endl;
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
				// if (curr->_key == key)
				// 	return (NULL);
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
			TreeNode* toDelete;
			while (1)
			{
				toDelete = this->findKey(key);
				if (toDelete == NULL)
					return ;

				// std::cout << key << std::endl;
				// this->show_tree(this->_root, "", true);
				this->_deleteNode(toDelete);
			}
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
			a->_key = temp_a._key;
			b->_key = temp_b._key;
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
			this->vector.push_back(root->_key);
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
	// srand(clock());
	RBTree tree;

	for (int i = 0; i < 100; ++i)
		tree.insertKey(rand() % 100);

	tree.show_tree(tree._root, "", true);
	tree.printInorder(tree._root);
	std::cout << std::endl;

	for (int i = 0; i < 100; ++i)
		tree.deleteKey(rand() % 100);

	tree.show_tree(tree._root, "", true);
	tree.vector.clear();
	tree.printInorder(tree._root);
	std::cout << std::endl;


	// tree.check_traversal();
	// std::sort(tree.vector.begin(), tree.vector.end());
	// for (int i = 0; i < tree.vector.size(); ++i)
	// {
	// 	std::cout << tree.vector[i] << " ";
	// 	if (i != tree.vector.size() - 1)
	// 		if (tree.vector[i] > tree.vector[i+1])
	// 		{
	// 			std::cout << "error!" << std::endl;
	// 			break ;	
	// 		}
	// }
	// std::cout << std::endl;

	// for (std::vector<int>::iterator iter = tree.vector.begin(); iter != tree.vector.end(); iter++)
	// 	std::cout << *iter << " ";
	// std::cout << std::endl;
}
