#pragma once

#include <iomanip>
#include <cassert>
#include <iostream>
#include <algorithm>

// ����Ž��Ʈ���� �����͸� �����ϴ� ������ ������ ���� : ó�� �ִ� ���� root�� �Ǿ����
// key�� ��Ұ��迡 ���� balance�� ���� �ʴ� tree�� �������(Ž���� ��ȿ����) 
// -> ���� ����Ʈ���� ��� �������� ���̰� ����ؾ߸� ȿ���� ����

template<typename K, typename V>
class BinarySearchTree
{
public:
	struct Item // key�� value�� ��(pair)
	{
		K key = K();	// first
		V value = V();	// second
	};

	struct Node
	{
		Item item;

		Node* left = nullptr;
		Node* right = nullptr;
	};

	void Preorder()
	{
		using namespace std;
		Preorder(root_);
		cout << endl;
	}

	void Preorder(Node* node)
	{
		using namespace std;
		if (node)
		{
			cout << node->item.key << " ";
			Preorder(node->left);
			Preorder(node->right);
		}
	}

	void Inorder()
	{
		using namespace std;
		Inorder(root_);
		cout << endl;
	}

	void Inorder(Node* node)
	{
		using namespace std;
		if (node)
		{
			Inorder(node->left);
			cout << node->item.key << " ";
			Inorder(node->right);
		}
	}

	Item* RecurGet(const K& key)
	{
	return RecurGet(root_, key);
	}

	Item* RecurGet(Node* node, const K& key)
	{
		if (!node) return nullptr; // <- ������ Ű�� ���� ��带 ã�� ���ϸ� nullptr�� ��ȯ�ϴ� ���

		if (key < node->item.key)
			return RecurGet(node->left, key);
		if (key > node->item.key)
			return RecurGet(node->right, key);

		return &node->item; // if (key == node->item.key)
	}

	Item* IterGet(const K& key)
	{
		// TODO:
		Node* node = root_;
		while (node)
		{
			if (node->item.key == key)
				return &node->item;
			else
			{
				if (node->item.key > key)
					node = node->left;
				if (node->item.key < key)
					node = node->right;
			}
		}

		return nullptr; // No matching
	}

	void Insert(const Item& item)
	{
		using namespace std;
		cout << "Insert " << item.key << item.value << endl;
		root_ = Insert(root_, item);
	}

	Node* Insert(Node* node, const Item& item)
	{
		// ��Ʈ: RecurGet()
		// TODO:
		if (!node) { return new Node{ item,nullptr,nullptr }; }

		if (node->item.key > item.key)
		{
			node->left = Insert(node->left, item);
		}

		if (node->item.key < item.key)
		{
			node->right = Insert(node->right, item);
		}

		if (node->item.key == item.key)
			node->item.value = item.value;

		// ���� �ؼ� : ������ �����
		//else
			//node->item = item;

		return node;
	}

	void IterInsert(const Item& item)
	{
		// TODO:
		std::cout << "IterInsert : " << item.key << item.value << std::endl;
		Node* node = root_;

		if (!node)
			root_ = new Node{ item,nullptr,nullptr };
		else
		{
			int fmnode = 0;    // left:0, right=1, same=2
			Node* former = nullptr;
			while (node)
			{
				if (node->item.key > item.key)
				{
					if (!node->left) { former = node; fmnode = 0; }
					node = node->left;
				}
				else if (node->item.key < item.key)
				{
					if (!node->right) { former = node; fmnode = 1; }
					node = node->right;
				}
				else
				{
					fmnode = 2;
					break;
				}
			}

			if (fmnode == 0) { former->left = new Node{ item,nullptr,nullptr }; }
			if (fmnode == 1) { former->right = new Node{ item,nullptr,nullptr }; }
			if (fmnode == 2) { node->item = item; }
		}
		
	}

	Node* MinKeyLeft(Node* node)
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
		if (!node) return node;

		if (key < node->item.key)
			node->left = Remove(node->left, key);
		else if (key > node->item.key)
			node->right = Remove(node->right, key);
		else   // key == node->item.key
		{
			// TODO:
			// �ڽ��� �ϳ��� ����
			if (node->left == nullptr && node->right == nullptr)
			{
				node = nullptr;
				return node;
			}

			// �ڽ��� �ϳ� ����
			if (node->left == nullptr && node->right != nullptr)
			{
				Node* temp = node;
				node = node->right;
				delete temp;
			}

			if (node->left != nullptr && node->right == nullptr)
			{
				Node* temp = node;
				node = node->left;
				delete temp;
			}
			
			// �ڽ��� 2�� �� ����
			if (node->left&&node->right)
			{
				Node* subs = MinKeyLeft(node->right);
				std::swap(subs->item, node->item);
				node->right = Remove(node->right, subs->item.key);
			}

			// ���� �ؼ�
			//if (!node->left)
			//{
			//	Node* temp = node->right;
			//	delete node;
			//	return temp;
			//}
			//else if (!node->right)
			//{
			//	Node* temp = node->left;
			//	delete node;
			//	return temp;
			//}

			//Node* temp = MinKeyNode(node->right);
			//node->item = temp->item;
			//node->right = Remove(node->right, temp->item.key);

		}

		return node;
	}

	int Height()
	{
		return Height(root_);
	}

	int Height(Node* node)
	{
		if (!node) return 0;
		return 1 + std::max(Height(node->left), Height(node->right));
	}

	void Print2D();
	void PrintLevel(int n);
	void DisplayLevel(Node* p, int lv, int d);

protected:
	Node* root_ = nullptr;
};

// ����� ���� ����
// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
template<typename K, typename V>
void BinarySearchTree<K, V>::Print2D()
{
	using namespace std;
	cout << "Height = " << Height() << endl;
	int i = 0;
	while (i < Height()) {
		PrintLevel(i);
		i++;
		cout << endl;
	}
	cout << endl;
}

template<typename K, typename V>
void BinarySearchTree<K, V>::PrintLevel(int n) {
	using namespace std;
	Node* temp = root_;
	int val = (int)pow(2.0, Height() - n + 1.0);
	cout << setw(val) << "";
	DisplayLevel(temp, n, val);
}

template<typename K, typename V>
void BinarySearchTree<K, V>::DisplayLevel(Node* p, int lv, int d) {
	using namespace std;
	int disp = 2 * d;
	if (lv == 0) {
		if (p == NULL) {
			cout << "   ";
			cout << setw(disp - 3) << "";
			return;
		}
		else {
			int result = ((p->item.key <= 1) ? 1 : (int)log10(p->item.key) + 1);
			cout << " " << p->item.key << p->item.value << " ";
			cout << setw(static_cast<streamsize>(disp) - result - 2) << "";
		}
	}
	else
	{
		if (p == NULL && lv >= 1) {
			DisplayLevel(NULL, lv - 1, d);
			DisplayLevel(NULL, lv - 1, d);
		}
		else {
			DisplayLevel(p->left, lv - 1, d);
			DisplayLevel(p->right, lv - 1, d);
		}
	}
}