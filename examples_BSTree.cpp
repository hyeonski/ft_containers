#include <iostream>

struct TreeNode
{
	TreeNode* _parent;
	TreeNode* _left;
	TreeNode* _right;
	int _data;

	// rbtree
	bool _red;

	TreeNode() : _parent(NULL), _left(NULL), _right(NULL), _data(0), _red(true) {}
	TreeNode(int value, TreeNode* parent) : _parent(parent), _left(NULL), _right(NULL), _data(value), _red(true) {}
	~TreeNode() {}
};

class BinarySearchTree
{
	public:
		TreeNode* _root;

		BinarySearchTree() : _root(NULL) {}

		TreeNode* findValue(int value)
		{
			TreeNode* curr = this->_root;

			if (this->_root == NULL) // 빈 트리일 경우
				return (NULL);
			while (1)
			{
				if (curr->_data == value)
					return (curr);
				else if (curr->_data > value)
				{
					if (curr->_left == NULL)
						return (NULL);
					curr = curr->_left;
				}
				else
				{
					if (curr->_right == NULL)
						return (NULL);
					curr = curr->_right;
				}
			}
		}

		virtual TreeNode* insertValue(int value) // 중복이면 오른쪽 서브트리에 삽입 - 그래야 중위순회 시 먼저 들어온 순서대로 출력된다
		{
			TreeNode* curr = this->_root;
			if (this->_root == NULL) // 빈 트리일 경우
			{
				this->_root = new TreeNode(value, NULL);
				return (this->_root);
			}
			while (1)
			{
				if (curr->_data == value)
				{
					if (curr->_right == NULL) // 중복 값인 노드이고 오른쪽 자식이 없는 경우
					{
						// 오른쪽에 insert
						TreeNode* newNode = new TreeNode(value, curr);
						curr->_right = newNode;
						return (newNode);
					}
					curr = curr->_right;
				}
				else if (curr->_data > value)
				{
					if (curr->_left == NULL) // insert 값이 노드보다 작고 왼쪽 자식이 없는 경우
					{
						// 왼쪽에 insert
						TreeNode* newNode = new TreeNode(value, curr);
						curr->_left = newNode;
						return (newNode);
					}
					curr = curr->_left;
				}
				else
				{
					if (curr->_right == NULL) // insert 값이 노드보다 작고 왼쪽 자식이 없는 경우
					{
						TreeNode* newNode = new TreeNode(value, curr);
						curr->_right = newNode;
						return (newNode);
					}
					curr = curr->_right;
				}
			}
		}
		virtual void deleteValue(int value)
		{
			TreeNode* toDelete = this->findValue(value);
			if (toDelete == NULL)
				return ;

			// 이진 탐색 트리 삭제 시 생각할 경우의 수
			// 1. 삭제하려는 노드의 자식이 없는가?
			// 2. 삭제하려는 노드가 하나의 서브트리만 가지는가? (왼쪽이든 오른쪽이든)
			// 3. 삭제하려는 노드가 두 서브트리를 모두 가지는가?


			// 삭제하려는 노드의 자식노드가 없는 경우
			if (toDelete->_left == NULL && toDelete->_right == NULL)
			{
				TreeNode* parent = toDelete->_parent;
				bool isLeft = this->isNodeParentLeft(parent, toDelete);
				if (isLeft) // 지우려는 노드가 부모의 왼쪽인지 오른쪽인지 파악하여 link 끊어준다
					parent->_left = NULL;
				else
					parent->_right = NULL;
				delete toDelete;
				return ;
			}
			// 왼쪽 서브트리만 가지는 경우
			else if (toDelete->_left != NULL && toDelete->_right == NULL)
			{
				TreeNode *parent = toDelete->_parent;
				if (parent != NULL)
				{
					bool isLeft = this->isNodeParentLeft(parent, toDelete);
					if (isLeft)
						parent->_left = NULL;
					else
						parent->_right = NULL;
					
					TreeNode* subTree = toDelete->_left;
					if (isLeft) // 삭제한 노드의 서브트리를 부모에게 연결해준다
						parent->_left = subTree;
					else
						parent->_right = subTree;
				}
				else // 지우려는 노드가 루트 노드인 경우
				{
					TreeNode* newRoot = toDelete->_left;
					newRoot->_parent = NULL;
					this->_root = newRoot;
				}
				delete toDelete;
			}
			// 오른쪽 서브트리만 가지는 경우
			else if (toDelete->_left == NULL && toDelete->_right != NULL)
			{
				TreeNode *parent = toDelete->_parent;
				if (parent != NULL)
				{
					bool isLeft = this->isNodeParentLeft(parent, toDelete);
					if (isLeft)
						parent->_left = NULL;
					else
						parent->_right = NULL;
					
					TreeNode* subTree = toDelete->_right;
					if (isLeft) // 삭제한 노드의 서브트리를 부모에게 연결해준다
						parent->_left = subTree;
					else
						parent->_right = subTree;
				}
				else // 지우려는 노드가 루트 노드인 경우
				{
					TreeNode* newRoot = toDelete->_right;
					newRoot->_parent = NULL;
					this->_root = newRoot;
				}
				delete toDelete;
			}
			// 오른쪽 왼쪽 서브트리 모두 가질 경우
			// 왼쪽 서브트리의 가장 큰 값 또는 오른쪽 가장 작은 값을 가진 노드를 연결한다
			else // 왼쪽 서브트리의 가장 큰 값을 기본으로 선택하도록 만들었다
			{
				TreeNode *switch_child;
				if (toDelete->_left != NULL) // 바꿔줄 최소 or 최대 노드 선택
					switch_child = this->getMaxNode(toDelete->_left);
				else
					switch_child = this->getMinNode(toDelete->_right);

				this->swapNode(toDelete, switch_child); // 선택된 단말 노드와 위치 바꿈

				if (this->isNodeParentLeft(toDelete->_parent, toDelete))
					toDelete->_parent->_left = NULL;
				else
					toDelete->_parent->_right = NULL;
				
				delete toDelete; // 맨 끝으로 위치가 바뀐 삭제할 노드를 삭제
			}
			
		}

		virtual bool isNodeParentLeft(TreeNode* parent, TreeNode* node)
		{
			if (parent->_left == node)
				return (true);
			else
				return (false);
		}

		virtual TreeNode* getMaxNode(TreeNode* root) // 반복문
		{
			TreeNode* curr = root;
			if (root == NULL)
				return (NULL);
			while (1)
			{
				if (curr->_right == NULL)
					return (curr);
				curr = curr->_right;
			}
			return (NULL);
		}

		// TreeNode* getMaxNode(TreeNode* root) // 재귀
		// {
		// 	if (root == NULL)
		// 		return (NULL);
		// 	if (root->_right == NULL)
		// 		return (root);
		// 	return (this->getMaxNode(root->_right));
		// }

		virtual TreeNode* getMinNode(TreeNode* root) // 반복문
		{
			TreeNode* curr = root;
			if (root == NULL)
				return (NULL);
			while (1)
			{
				if (curr->_left == NULL)
					return (curr);
				curr = curr->_left;
			}
			return (NULL);
		}

		// TreeNode* getMinNode(TreeNode* root) // 재귀
		// {
		// 	if (root == NULL)
		// 		return (NULL);
		// 	if (root->_left == NULL)
		// 		return (root);
		// 	return (this->getMaxNode(root->_left));
		// }

		virtual void swapNode(TreeNode* a, TreeNode* b)
		{
			// 부모 자식 바꿔주는게 조금 귀찮음...
			TreeNode* tempParent = a->_parent;
			TreeNode* tempLeft = a->_left;
			TreeNode* tempRight = a->_right;

			TreeNode* aParent = a->_parent;
			TreeNode* aLeft = a->_left;
			TreeNode* aRight = a->_right;
			TreeNode* bParent = b->_parent;
			TreeNode* bLeft = b->_left;
			TreeNode* bRight = b->_right;

			// 부모의 자식 포인터 바꿔주기
			if (aParent != NULL)
			{
				bool isLeft = this->isNodeParentLeft(aParent, a);
				if (isLeft)
					aParent->_left = b;
				else
					aParent->_right = b;
			}
			if (bParent != NULL)
			{
				bool isLeft = this->isNodeParentLeft(bParent, b);
				if (isLeft)
					bParent->_left = a;
				else
					bParent->_right = a;
			}

			// a의 오른쪽-왼쪽 자식의 부모 포인터 바꿔주기
			if (a->_left != NULL)
				aLeft->_parent = b;
			if (a->_right != NULL)
				aRight->_parent = b;
			
			// b의 오른쪽-왼쪽 자식의 부모 포인터 바꿔주기
			if (b->_left != NULL)
				bLeft->_parent = a;
			if (b->_right != NULL)
				bRight->_parent = a;

			// 이제 노드 스왑
			a->_parent = b->_parent;
			a->_left = b->_left;
			a->_right = b->_right;

			b->_parent = tempParent;
			b->_left = tempLeft;
			b->_right = tempRight;
		}

		void printInOrder(TreeNode* root)
		{
			if (root == NULL)
				return ;
			printInOrder(root->_left);
			std::cout << root->_data << " ";
			printInOrder(root->_right);
		}
};

int main(void)
{
	// srand(clock());

	BinarySearchTree bst;
	for (int i = 0; i < 20; ++i)
		bst.insertValue(rand() % 100);
	bst.printInOrder(bst._root);
	std::cout << std::endl;


	std::cout << std::endl << "find test" << std::endl;
	int toDelete;

	toDelete = rand() % 100;
	TreeNode* finded = bst.findValue(toDelete);
	if (finded == NULL)
		std::cout << "not founded " << toDelete << "!" << std::endl;
	else
	{
		std::cout << "tried to find " << toDelete << ":" << std::endl;
		std::cout << "finded:" << finded->_data << std::endl;
	}


	toDelete = rand() % 100;
	finded = bst.findValue(toDelete);
	if (finded == NULL)
		std::cout << "not founded " << toDelete << "!" << std::endl;
	else
	{
		std::cout << "tried to find " << toDelete << ":" << std::endl;
		std::cout << "finded:" << finded->_data << std::endl;
	}

	std::cout << std::endl << "delete test" << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		toDelete = rand() % 100;
		bst.deleteValue(toDelete);
		std::cout << "try to delete:" << toDelete << std::endl;
		bst.printInOrder(bst._root);
		std::cout << std::endl;
	}
	bst.printInOrder(bst._root);
	std::cout << std::endl;
	
// }