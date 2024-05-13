#pragma once

template <typename T>
struct Node
{
	Node<T>* parent = nullptr;
	T value;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
};

template <typename T>
class BinaryTree
{
	Node<T>* root;
	int size;
public:

	BinaryTree();
	~BinaryTree() {};

	Node<T>* Root() const;
	int Size() const;

	Node<T>* CreateNode(Node<T>* parent, T value);

	void AddLoop(T value);
	void AddReq(T value, Node<T>* node = nullptr);

	Node<T>* FindLoop(T value);
	Node<T>* FindReq(T value);

	Node<T>* MinBranch(Node<T>* node = nullptr);
	Node<T>* MaxBranch(Node<T>* node = nullptr);

	void DeleteNode(Node<T>* node);
	void DeleteBranch(Node<T>* node);

	void ListBranch(Node<T>* node);
	void List();
};

template<typename T>
inline BinaryTree<T>::BinaryTree() : root{}, size{} {}

template<typename T>
inline Node<T>* BinaryTree<T>::Root() const
{
	return root;
}

template<typename T>
inline int BinaryTree<T>::Size() const
{
	return size;
}

template<typename T>
inline Node<T>* BinaryTree<T>::CreateNode(Node<T>* parent, T value)
{
	Node<T>* node = new Node<T>;
	node->parent = parent;
	node->value = value;
	return node;
}

template<typename T>
inline void BinaryTree<T>::AddLoop(T value)
{
	size++;

	if (!root)
	{
		root = CreateNode(nullptr, value);
		return;
	}

	Node<T>* nodeParent = nullptr;
	Node<T>* nodeCurrent = root;

	while (nodeCurrent)
	{
		nodeParent = nodeCurrent;
		if (value < nodeCurrent->value)
			nodeCurrent = nodeCurrent->left;
		else
			nodeCurrent = nodeCurrent->right;
	}

	nodeCurrent = CreateNode(nodeParent, value);
	if (value < nodeParent->value)
		nodeParent->left = nodeCurrent;
	else
		nodeParent->right = nodeCurrent;

}

template<typename T>
inline void BinaryTree<T>::AddReq(T value, Node<T>* node)
{
	if (!root)
	{
		root = CreateNode(nullptr, value);
		size++;
		return;
	}

	if (!node)
		node = root;

	if (value < node->value)
	{
		if (node->left)
			AddReq(value, node->left);
		else
		{
			node->left = CreateNode(node, value);
			size++;
		}
	}
	else
	{
		if (node->right)
			AddReq(value, node->right);
		else
		{
			node->right = CreateNode(node, value);
			size++;
		}
	}
}

template<typename T>
inline Node<T>* BinaryTree<T>::FindLoop(T value)
{
	Node<T>* nodeCurrent = root;
	
	while (nodeCurrent)
	{
		if (value == nodeCurrent->value)
			return nodeCurrent;
		else
		{
			if (value < nodeCurrent->value)
				nodeCurrent = nodeCurrent->left;
			else
				nodeCurrent = nodeCurrent->right;
		}
	}
	return nullptr;
}

template<typename T>
inline Node<T>* BinaryTree<T>::MinBranch(Node<T>* node)
{
	if (!node)
		node = root;
	while (node->left)
		node = node->left;
	return node;
}

template<typename T>
inline Node<T>* BinaryTree<T>::MaxBranch(Node<T>* node)
{
	if (!node)
		node = root;
	while (node->right)
		node = node->right;
	return node;
}

template<typename T>
inline void BinaryTree<T>::DeleteNode(Node<T>* node)
{
	// delete leaf
	if (!node->left && !node->right)
	{
		if (node == root)
			root = nullptr;
		else
		{
			if (node->parent->left == node)
				node->parent->left = nullptr;
			else
				node->parent->right = nullptr;
		}
		delete node;
		size--;
		return;
	}

	// delete node with single child
	if ((bool)node->left ^ (bool)node->right)
	{
		Node<T>* child;
		/*if (node->left)
			child = ;
		else
			child = node->right;*/

		child = (node->left) ? node->left : node->right;

		if (node == root)
		{
			root = child;
			child->parent = nullptr;
		}
		else
		{
			if (node->parent->left == node)
				node->parent->left = child;
			else
				node->parent->right = child;
			child->parent = node->parent;
		}
		delete node;
		size--;
		return;
	}

	// delete node with pair childrens;
	Node<T>* nodeMinRight = MinBranch(node->right);
	node->value = nodeMinRight->value;
	DeleteNode(nodeMinRight);
}

template<typename T>
inline void BinaryTree<T>::ListBranch(Node<T>* node)
{
	if (node)
	{
		ListBranch(node->left);
		std::cout << node->value << " ";
		ListBranch(node->right);
	}
}

template<typename T>
inline void BinaryTree<T>::List()
{
	ListBranch(root);
}
