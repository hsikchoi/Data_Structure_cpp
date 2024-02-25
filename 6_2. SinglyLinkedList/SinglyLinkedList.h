#pragma once

#include <cassert>
#include <stdint.h>

template<typename T>
class SinglyLinkedList
{
public:
	struct Node
	{
		T item = T();
		Node* next = nullptr;
	};

	SinglyLinkedList()
	{
	}

	SinglyLinkedList(const SinglyLinkedList& list)
	{
		// TODO: ���� ����Ʈ ����
		Node* cpy = first_;
		Node* current = list.first_;
		while (current)
		{
			PushBack(current->item);
			current = current->next;
		}
	}

	~SinglyLinkedList()
	{
		Clear();
	}

	void Clear() // ��� ������(delete) �մϴ�.
	{
		// TODO: ��� ����
		if (!IsEmpty())
		{
			Node* current = first_;
			while (current)
			{
				Node* del = current;
				current = current->next;
				delete del;
			}
		}

		// �� ����
		/*while (first_)
			PopFront();*/
	}

	bool IsEmpty()
	{
		return first_ == nullptr;
	}

	int Size()
	{
		int size = 0;

		// TODO: size�� �ϳ��ϳ� ��� ��ȯ
		Node* current = first_;
		while (current)
		{
			size++;
			current = current->next;
		}

		return size;
	}

	T Front()
	{
		assert(first_);

		return first_->item; // TODO: ����
	}

	T Back()
	{
		assert(first_);

		Node* current = first_;
		while (current->next)
			current = current->next;

		return current->item; // TODO: ����
	}

	Node* Find(T item)
	{
		// TODO: item�� ������ ��� ������ ��ȯ
		Node* current = first_;
		while (current)
		{
			if (current->item == item)
				return current;
			current = current->next;
		}

		return nullptr;
	}

	void InsertBack(Node* node, T item)
	{
		// TODO:
		Node* insert = new Node;
		insert->item = item;

		Node* next_ = node->next;
		node->next = insert;
		insert->next = next_;
	}

	void Remove(Node* n)
	{
		assert(first_);

		// �ϳ� ���� ��带 ã�ƾ� �մϴ�.
		// TODO:
		Node* current = first_;

		if (first_ == n)
		{
			first_ = first_->next;
			delete n;
			return;
		}

		while (current->next != n)
			current = current->next;
		Node* temp = n->next;
		current->next = temp;
		delete n;
	}

	void PushFront(T item)
	{
		// first_�� nullptr�� ���� �ƴ� ��� ������ �����غ��� (�ᱹ�� �� ��츦 �ϳ��� ��ĥ �� ����)

		// ���ο� ��� �����
		// TODO:
		Node* new_ = new Node;
		new_->item = item;

		// ���� ���� ����
		// TODO:
		if (first_)
		{
			new_->next = first_;
			first_ = new_;
		}
		else
		{
			first_ = new_;
		}
	}

	void PushBack(T item)
	{
		Node* back = new Node;
		back->item = item;
		if (first_)
		{
			// TODO:
			Node* current = first_;
			while (current->next)
				current = current->next;
			current->next = back;
		}
		else
		{
			// TODO:
			first_ = back;
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

		Node* temp = first_;
		first_ = first_->next;

		// TODO: �޸� ����
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

		if (first_->next == nullptr)
		{
			delete first_;
			first_ = nullptr;
		}

		// �� �ڿ��� �ϳ� ���� ��带 ã�ƾ� �մϴ�.
		assert(first_);

		Node* current = first_;
		while (current->next->next)
			current = current->next;

		Node* wait_delete = current->next;
		current->next = nullptr;

		

		// TODO: �޸� ����
		delete wait_delete;
	}

	void Reverse() // �ٽ� �����غ���
	{
		// TODO:
		Node* current = first_;
		Node* prev = nullptr;
		while (current)
		{
			Node* temp = prev;
			prev = current;
			current = current->next;
			prev->next = temp;
		}
		first_ = prev;

	}

	void SetPrintDebug(bool flag)
	{
		print_debug_ = flag;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << " ";

			while (current)
			{
				if (print_debug_)
				{
					//cout << "[" << current << ", " << current->item << ", " << current->next << "]";

					// �ּҸ� ª�� ������ ��� (�� �κ��� ��κ� �����ϱ⶧���� �޺κи� ���)
					cout << "[" << reinterpret_cast<uintptr_t>(current) % 100000 << ", "
						<< current->item << ", "
						<< reinterpret_cast<uintptr_t>(current->next) % 100000 << "]";
				}
				else
				{
					cout << current->item;
				}

				if (current->next)
					cout << " -> ";
				else
					cout << " -> NULL";

				current = current->next;
			}
			cout << endl;
		}
	}

protected:
	Node* first_ = nullptr;

	bool print_debug_ = false;
};