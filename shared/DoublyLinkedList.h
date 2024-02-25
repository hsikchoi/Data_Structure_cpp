#pragma once

#include <cassert>
#include <stdint.h>
#include <algorithm>

template<typename T>
class DoublyLinkedList
{
public:
	struct Node
	{
		T item = T();

		Node* left = nullptr;
		Node* right = nullptr;

		// ����: prev/next�� �ƴ϶� left/right
	};

	DoublyLinkedList()
	{
	}

	DoublyLinkedList(const DoublyLinkedList& list)
	{
		Node* current = list.first_;
		while (current)
		{
			PushBack(current->item);
			current = current->right;
		}
	}

	~DoublyLinkedList()
	{
		Clear();
	}

	void Clear() // ��� ������(delete) �մϴ�.
	{
		// TODO:
		if (first_)
			PopFront();

	}

	bool IsEmpty()
	{
		return first_ == nullptr; // TODO:
	}

	int Size()
	{
		int size = 0;

		// TODO:
		Node* current = first_;
		while (current)
		{
			size++;
			current = current->right;
		}

		return size;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << endl;

			cout << " Forward: ";
			// TODO:
			while (true)
			{
				cout << current->item << " ";

				if (current->right)
					current = current->right;
				else
					break;
			}
			cout << endl;

			cout << "Backward: ";
			// TODO:

			while(true)
			{
				cout << current->item << " ";

				if (current->left)
					current = current->left;
				else
					break;
			}
			cout << endl;
		}
	}

	Node* Find(T item)
	{
		Node* current = first_;
		while (current)
		{
			if (current->item == item)
				return current;
			current = current->right;
		}

		return nullptr; // TODO:
	}

	void InsertBack(Node* node, T item)
	{
		if (IsEmpty())
		{
			PushBack(item);
		}
		else
		{
			// TODO:
			Node* back = new Node;
			back->item = item;

			back->right = node->right;
			node->right = back;
			

			back->left = node;

			if (back->right)
				back->right->left = back;

			
		}
	}

	void PushFront(T item)
	{
		// TODO:
		Node* front = new Node;
		front->item = item;

		if (IsEmpty())
			first_ = front;
		else
		{
			first_->left = front;
			front->right = first_;
			first_ = front;
		}

	}

	void PushBack(T item)
	{
		// TODO:
		Node* back = new Node;
		back->item = item;

		if (IsEmpty())
			first_ = back;
		else
		{
			Node* current = first_;
			while (current->right)
				current = current->right;
			current->right = back;
			back->left = current;
		}
	}

	void PopFront()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopFront()" << endl;
			return;
		}

		assert(first_);

		// TODO:
		
		/*Node* current = first_;
		Node* temp = nullptr;
		temp = current;
		if (current->right)                 // ���� : nullptr�� ���� ������ �޸� ���� �߻�
		{
			current = current->right;
			current->left = nullptr;
			temp->right = nullptr;
			first_ = current;
			delete temp;
		}
		else
			delete temp;*/

		Node* temp = first_;
		first_ = first_->right;
		if (first_)
			first_->left = nullptr;
		delete temp;

	}

	void PopBack()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}

		// �� �ڿ��� �ϳ� ���� ��带 ã�ƾ� �մϴ�.

		assert(first_);

		// TODO:
		
		Node* current = first_;

		if (current->right)
		{
			while (current->right->right)
				current = current->right;

			Node* temp = current->right;
			current->right = nullptr;

			delete temp;
		}
		else
		{
			delete first_;
			first_ = nullptr;
		}
	}

	void Reverse() // �ٽ� ���� : single������ �Ȱ��� ������� �ٽ��غ���
	{
		// TODO:
		Node* current = first_;
		Node* prev = nullptr;

		while (current)
		{
			prev = current;
			current = current->right;
			std::swap(prev->right, prev->left);
		}
		first_ = prev;
	}

	T Front()
	{
		assert(first_);

		return first_->item; // TODO:
	}

	T Back()
	{
		assert(first_);

		Node* current = first_;
		while (current->right)
			current = current->right;

		return current->item; // TODO:
	}

protected:
	Node* first_ = nullptr;
};