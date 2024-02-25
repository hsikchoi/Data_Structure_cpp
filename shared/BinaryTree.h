#pragma once

#include <iostream>
#include <fstream>
#include <string> // BinaryTree ���

#include "../shared/Queue.h"
#include "../shared/Stack.h"

template<typename T>
class BinaryTree
{
public:
	struct Node
	{
		T item = T();
		Node* left = nullptr; // Left child
		Node* right = nullptr; // Right child
	};

	// ����� ����: ť���� �ּ� ��ſ� ������ ���
	class MyQueue : public Queue<Node*>
	{
	public:
		void Print()
		{
			using namespace std;

			for (int i = (this->front_ + 1) % this->capacity_; i != (this->rear_ + 1) % this->capacity_; i = (i + 1) % this->capacity_)
				cout << this->queue_[i]->item << " ";
			cout << endl;
		}
	};

	// ����� ����: ���ÿ��� �ּ� ��ſ� ������ ���
	class MyStack : public Stack<Node*>
	{
	public:
		void Print()
		{
			using namespace std;

			for (int i = 0; i < this->Size(); i++)
				cout << this->stack_[i]->item << " ";
			cout << endl;
		}
	};

	BinaryTree() {}

	BinaryTree(Node* root)
	{
		root_ = root;
	}

	bool IsEmpty()
	{
		return root_ == nullptr;
	}

	void Visit(Node* node)
	{
		using namespace std;
		cout << node->item << " "; // �����ϰ� ���� �۾� ����(���⼭�� ���)
	}

	int Sum()
	{
		return Sum(root_);
	}

	int Sum(Node* node)
	{
		if (node == nullptr)
			return 0;

		if (node->left == nullptr&&node->right == nullptr)
			return node->item;

		return node->item + Sum(node->left) + Sum(node->right); // TODO:
	}

	int Height()
	{
		return Height(root_);
	}

	int Height(Node* node)
	{
		if (node == nullptr)
			return 0;


		return 1 + (Height(node->left) >= Height(node->right) ? Height(node->left) : Height(node->right)); // TODO:
	}

	~BinaryTree()
	{
		DeleteTree(root_);
	}

	void DeleteTree(Node* node)
	{
		if (node)
		{
			// TODO: ��Ʈ Post-order
		}
	}

	void Preorder() { Preorder(root_); }
	void Preorder(Node* node)
	{
		// TODO:
		if (node)
		{
			Visit(node);
			Preorder(node->left);
			Preorder(node->right);
		}
	};

	void Inorder() { Inorder(root_); }
	void Inorder(Node* node)
	{
		// TODO:
		if (node)
		{
			Inorder(node->left);
			Visit(node);
			Inorder(node->right);
		}
	}

	void Postorder() { Postorder(root_); }
	void Postorder(Node* node)
	{
		// TODO:
		if (node)
		{
			Postorder(node->left);
			Postorder(node->right);
			Visit(node);
		}
	}

	void LevelOrder() // ��Ǯ����
	{
		MyQueue q; // ��Ʈ: MyQueue q;
		Node* current = root_;
		while (current)
		{
			Visit(current);
			// TODO:
			if (current->left) { q.Enqueue(current->left); };
			if (current->right) { q.Enqueue(current->right); };
			if (q.IsEmpty()) return;

			current = q.Front();
			q.Dequeue();
		}
		q.Print();
	}

	void IterPreorder()
	{
		if (!root_) return;

		MyStack s; // ��Ʈ: MyStack q;
		s.Push(root_);
		Node* current = root_;
		
		while (!s.IsEmpty())
		{
			//TODO:
			Visit(current);

			if (current->right) { s.Push(current->right); }
			if (current->left) { s.Push(current->left); }
			
			current = s.Top();
			s.Pop();
		}
		
	}

	void IterInorder()
	{
		if (!root_) return;

		MyStack s;
	
		Node* current = root_;
		while (current || !s.IsEmpty())
		{
			// TODO:
			
			while (current)
			{
				s.Push(current);
				current = current->left;
			}
			
			current = s.Top();
			Visit(current);
			s.Pop();

			current = current->right;
		}
	}

	void IterPostorder()
	{
		if (!root_) return;

		Stack<Node*> s1, s2;
		s1.Push(root_);

		while (!s1.IsEmpty())
		{
			// TODO:
		}

		while (!s2.IsEmpty())
		{
			// TODO:
		}
	}

	void Print2D();
	void PrintLevel(int n);
	void DisplayLevel(Node* p, int lv, int d);

protected:
	Node* root_ = nullptr;
};

// ����� ���� ����
// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
template<typename T>
void BinaryTree<T>::Print2D()
{
	using namespace std;
	int i = 0;
	while (i < Height()) {
		PrintLevel(i);
		i++;
		cout << endl;
	}
}

template<typename T>
void BinaryTree<T>::PrintLevel(int n) {
	using namespace std;
	Node* temp = root_;
	int val = (int)pow(2.0, Height() - n + 1.0);
	cout << setw(val) << "";
	DisplayLevel(temp, n, val);
}

template<typename T>
void BinaryTree<T>::DisplayLevel(Node* p, int lv, int d) {
	using namespace std;
	int disp = 2 * d;
	if (lv == 0) {
		if (p == NULL) {
			cout << "   ";
			cout << setw(disp - 3) << "";
			return;
		}
		else {
			int result = ((p->item <= 1) ? 1 : (int)log10(p->item) + 1);
			cout << " " << p->item << " ";
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