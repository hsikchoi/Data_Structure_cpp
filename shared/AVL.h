#pragma once

#include "../shared/BinarySearchTree.h"

//Georgy Adelson - Velsky and Evgenii Landis Ʈ��
//
//������ ������ ���簣�ٰ� �ؼ� self - balancing binary search tree��� �θ��ϴ�.�����ϸ� "�ڰ� ���� ���� �˻� Ʈ��" ������ �� �� �����ϴ�.
//
//AVL Ʈ���� ������ ������ �ֱ� ������ ����, ����, Ž���� ��� / �־� �ð� ���⵵�� ��� O(logN)�� �˴ϴ�.
//
//���� ���������� ���̸� �Ź� ���� ����ϰ� �ִµ� ��귮�� ���̱� ���ؼ� Node�� �����ؼ� �����ϰ� ��ſ� ���� �ٲ𶧸� ������Ʈ �ϴ� ����� �ֽ��ϴ�.

template<typename K, typename V>
class AVL : public BinarySearchTree<K, V>
{
public:
	using Base = BinarySearchTree<K, V>;
	using Item = BinarySearchTree<K, V>::Item;
	using Node = BinarySearchTree<K, V>::Node;

	//struct Item {
	//	K key = K();	// first
	//	V value = V();	// second
	//};

	//struct Node {
	//	Item item;
	//	Node* left = nullptr;
	//	Node* right = nullptr;
	//};

	int Height(Node* node)
	{
		return Base::Height(node); // �򰥸� ������
	}

	int Balance(Node* node)
	{
		if (node)
			return Base::Height(node->left) - Base::Height(node->right);
		else
			return 0;
	}

	Node* RotateLeft(Node* parent)
	{
		// TODO:
		Node* node = parent->right;
		Node* temp = nullptr;
		if (node->right)
			temp = node->right;
		node->left = parent;
		parent->right = temp;
		root_ = node;

		return node;

		// ���� �ؼ�
		//Node* child = parent->right;
		//parent->right = child->left;
		//child->left = parent;
		//return child;
	}

	Node* RotateRight(Node* parent)
	{
		// TODO:
		Node* node = parent->left;
		Node* temp = nullptr;
		if (node->right)
			temp = node->right;
		node->right = parent;
		parent->left = temp;
		root_ = node;

		return node;

		// ���� �ؼ�
		//Node* child = parent->left;
		//parent->right = child->right;
		//child->right = parent;
		//return child;
	}

	void Insert(const Item& item)
	{
		using namespace std;
		cout << "Insert " << item.key << endl;
		root_ = Insert(root_, item);
	}

	Node* Insert(Node* node, const Item& item)
	{
		if (!node)
			return new Node{ item, nullptr, nullptr };

		const auto& key = item.key;

		if (key < node->item.key)
			node->left = Insert(node->left, item);
		else if (key > node->item.key)
			node->right = Insert(node->right, item);
		else
		{
			node->item = item;
			return node;
		}

		int balance = Balance(node);

		// balance�� 0, 1, -1 �̸� ������ �ʿ䰡 ���ٰ� �Ǵ�

		// LL -> Right Rotation
		//	TODO:
		if (balance > 1 && Balance(node->left) >= 0)
			node = RotateRight(node);

		// RR -> Left Rotation
		//	TODO:
		if (balance < -1 && Balance(node->right) <= 0)
			node = RotateLeft(node);
		

		// LR -> Left-Right Rotation
		if (balance > 1 && Balance(node->left) < 0)
		{ // TODO:
			node->left = RotateLeft(node->left);
			node = RotateRight(node);
		}

		// RL -> Right-Left Rotation
		if (balance < -1 && Balance(node->right) > 0)
		{ // TODO:
			node->right = RotateRight(node->right);
			node = RotateLeft(node);
		}

		return node;
	}

	Node* MinKeyNode(Node* node)
	{
		assert(node);
		while (node->left)
			node = node->left;
		return node;
	}

	void Remove(const K& key)
	{
		using namespace std;
		cout << "Remove " << key << endl;
		root_ = Remove(root_, key);
	}

	Node* Remove(Node* node, const K& key)
	{
		// BST�� ����
		if (!node) return node;

		if (key < node->item.key)
			node->left = Remove(node->left, key);
		else if (key > node->item.key)
			node->right = Remove(node->right, key);
		else
		{
			if (!node->left)
			{
				Node* temp = node->right;
				delete node;
				return temp;
			}
			else if (!node->right)
			{
				Node* temp = node->left;
				delete node;
				return temp;
			}

			Node* temp = MinKeyNode(node->right);
			node->item = temp->item;
			node->right = Remove(node->right, temp->item.key);
		}

		if (node == NULL)
			return node;

		// ���� ���

		int balance = Balance(node);

		// TODO:
		// balance�� 0, 1, -1 �̸� ������ �ʿ䰡 ���ٰ� �Ǵ�

		// LL -> Right Rotation
		if (balance > 1 && Balance(node->left) >= 0)
			node = RotateRight(node);

		// RR -> Left Rotation
		if (balance < -1 && Balance(node->right) <= 0)
			node = RotateLeft(node);

		// LR -> Left-Right Rotation
		if (balance > 1 && Balance(node->left) < 0)
		{ 
			node->left = RotateLeft(node->left);
			node = RotateRight(node);
		}

		// RL -> Right-Left Rotation
		if (balance < -1 && Balance(node->right) > 0)
		{
			node->right = RotateRight(node->right);
			node = RotateLeft(node);
		}


		return node;
	}

private:
	Node*& root_ = BinarySearchTree<K, V>::root_;
	// this->root_�ε� ��� ����
};