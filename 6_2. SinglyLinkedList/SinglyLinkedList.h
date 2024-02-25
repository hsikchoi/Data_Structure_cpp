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
		// TODO: 연결 리스트 복사
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

	void Clear() // 모두 지워야(delete) 합니다.
	{
		// TODO: 모두 삭제
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

		// 더 간단
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

		// TODO: size를 하나하나 세어서 반환
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

		return first_->item; // TODO: 수정
	}

	T Back()
	{
		assert(first_);

		Node* current = first_;
		while (current->next)
			current = current->next;

		return current->item; // TODO: 수정
	}

	Node* Find(T item)
	{
		// TODO: item이 동일한 노드 포인터 반환
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

		// 하나 앞의 노드를 찾아야 합니다.
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
		// first_가 nullptr인 경우와 아닌 경우 나눠서 생각해보기 (결국은 두 경우를 하나로 합칠 수 있음)

		// 새로운 노드 만들기
		// TODO:
		Node* new_ = new Node;
		new_->item = item;

		// 연결 관계 정리
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

		// TODO: 메모리 삭제
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

		// 맨 뒤에서 하나 앞의 노드를 찾아야 합니다.
		assert(first_);

		Node* current = first_;
		while (current->next->next)
			current = current->next;

		Node* wait_delete = current->next;
		current->next = nullptr;

		

		// TODO: 메모리 삭제
		delete wait_delete;
	}

	void Reverse() // 다시 생각해보기
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

					// 주소를 짧은 정수로 출력 (앞 부분은 대부분 동일하기때문에 뒷부분만 출력)
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