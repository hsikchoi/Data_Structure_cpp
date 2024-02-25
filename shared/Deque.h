#pragma once

#include "../shared/Queue.h"

#include <cassert>
#include <iostream>
#include <iomanip>

// Double Ended Queue (郸, dequeue客 备盒)
template<typename T>
class Deque : public Queue<T>
{

	typedef Queue<T> Base;

public:
	Deque(int capacity)
		: Queue<T>(capacity)
	{
	}

	T& Front()
	{
		return Base::Front();
	}

	T& Back()
	{
		return Base::Rear();
	}

	void PushFront(const T& item)
	{
		if (Base::IsFull())
			Base::Resize();
		// TODO:
		Base::queue_[Base::front_] = item;
		Base::front_ = (Base::front_ - 1 + Base::capacity_) % Base::capacity_;

		/*queue_[front_] = item;
		front_ = (front_ - 1 + capacity_) % capacity_;*/
	}

	void PushBack(const T& item)
	{
		Base::Enqueue(item);
	}

	void PopFront()
	{
		Base::Dequeue();
	}

	void PopBack()
	{
		assert(!Base::IsEmpty());

		// TODO:
		Base::rear_ = (Base::rear_ - 1 + Base::capacity_) % Base::capacity_;

		//rear_ = (rear_ - 1 + capacity_) % capacity_;
	}

private:
	// Queue客 悼老
	/*T* queue_ = Base::queue_; 
	int& front_ = Base::front_; 
	int& rear_ = Base::rear_; 
	int& capacity_ = Base::capacity_; 
	bool& print_debug_ = Base::print_debug_;*/
};