#pragma once

#include <iomanip>
#include <cassert>
#include <iostream>
#include <algorithm>

// 이진탐색트리는 데이터를 저장하는 순서에 영향을 받음 : 처음 넣는 값이 root가 되어버림
// key의 대소관계에 따라 balance가 맞지 않는 tree가 만들어짐(탐색에 비효율적) 
// -> 양쪽 서브트리의 노드 개수보다 깊이가 비슷해야만 효율이 높음

template<typename K, typename V>
class BinarySearchTree
{
public:
	struct Item // key와 value의 쌍(pair)
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
		if (!node) return nullptr; // <- 동일한 키를 가진 노드를 찾지 못하면 nullptr을 반환하는 기능

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
		// 힌트: RecurGet()
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

		// 강의 해설 : 같으면 덮어쓰기
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
			// 자식이 하나도 없음
			if (node->left == nullptr && node->right == nullptr)
			{
				node = nullptr;
				return node;
			}

			// 자식이 하나 있음
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
			
			// 자식이 2개 다 있음
			if (node->left&&node->right)
			{
				Node* subs = MinKeyLeft(node->right);
				std::swap(subs->item, node->item);
				node->right = Remove(node->right, subs->item.key);
			}

			// 강의 해설
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

// 디버깅 편의 도구
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