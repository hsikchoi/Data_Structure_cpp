#pragma once

#include <cassert>
#include <iostream>

template<typename T> // 템플릿 사용
class Stack
{
public:
	Stack(int capacity = 1)
	{
		assert(capacity > 0);
		Resize(capacity);
	}

	~Stack()
	{
		if (stack_) delete[] stack_;
	}

	void Resize(int new_capacity)
	{
		T* new_stack = new T[new_capacity];
		memcpy(new_stack, stack_, sizeof(T) * Size());
		if (stack_) delete[] stack_;
		stack_ = new_stack;
		capacity_ = new_capacity;
	}

	bool IsEmpty() const
	{
		if (top_ == -1)
			return true;
		else
			return false; // TODO:

		//return top_ == -1;
	}

	int Size() const
	{
		if (top_ != -1)
			return top_ + 1;

		else 
			return 0; //TODO:

		//return top_ + 1;
	}

	void Print()
	{
		using namespace std;

		for (int i = 0; i < Size(); i++) // Size() 사용
			cout << stack_[i] << " ";
		cout << endl;
	}

	// Returns TOP element of stack.
	T& Top() const
	{
		assert(!IsEmpty());

		return stack_[top_];
	}

	// Insert item into the TOP of the stack
	void Push(const T& item)
	{
		// TODO: 필요하면 리사이즈 
		if (capacity_ < Size()+sizeof(item) / sizeof(T))
			Resize(Size() + sizeof(item) / sizeof(T));

		/*if (top_ == capacity_ - 1)
			Resize(capacity_ * 2);*/

		// TODO:
		stack_[top_ + 1] = item;
		top_++;

		//stack_[++top_] = item;
	}

	// Delete the TOP element of the stack
	void Pop()
	{
		assert(!IsEmpty());

		// TODO:
		T* pop_stack = new T[capacity_ - 1];
		memcpy(pop_stack, stack_, sizeof(T) * (capacity_ - 1));
		if (stack_) delete[] stack_;
		stack_ = pop_stack;
		top_--;
		capacity_--;

		//top_--;    // top_의 위치만 바꾸면 된다 : 메모리는 변경x
		//stack_[top_--].~T();   // 소멸자 수동 호출

	}

protected: // 뒤에서 상속해서 사용
	T* stack_ = nullptr;
	int top_ = -1; // 0 아님
	int capacity_ = 0;
};