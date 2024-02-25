//#include "../shared/Deque.h"
#include "Deque.h"

#include <iostream>

int main()
{
	// Double Ended Queue (덱) : Queue 기능 확장 - 양쪽을 모두 사용할 수 있는 자료구조
	Deque<char> d(8);

	d.SetDebugFlag(true);

	d.Print();

	d.PushFront('A');
	d.Print();

	d.PushFront('B');
	d.Print();

	d.PushBack('C');
	d.Print();

	d.PushBack('D');
	d.Print();

	d.PopFront();
	d.Print();

	d.PopBack();
	d.Print();

	return 0;
}