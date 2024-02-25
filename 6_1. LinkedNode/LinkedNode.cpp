#include <iostream>

using namespace std;

// sequential representation : 전체를 탐색하는 process가 많을 때 유용 / 데이터 삽입 삭제가 빈번한 경우에는 비효율적
// 데이터를 각각 떨어뜨려 놓으면 어떨까? 각각의 주소만 알면 데이터를 찾아갈 수 있음
// -> 주소를 관리하는게 중요한 task -> 주소를 한곳에 모으면 결국 배열이 되기 때문에 sequential representation이 됨
// 데이터에 다음 데이터에 대한 링크를 같이 저장한다 : 데이터가 저장된 노드 한 개에 데이터+다음 노드에 대한 포인터를 함께 저장 -> linked representation


struct Node
{
	int item = 0;	  // <- 큰 데이터도 가능
	Node* next = nullptr;

	friend ostream& operator<<(ostream& os, const Node& n)
	{
		cout << "[" << &n << ", " << n.item << ", " << n.next << "]" << flush;
		return os;
	}
};

void RecurPrint(Node* node)
{
	// TODO: 메모리 에러 나는 이유 파악
	/*cout << *node << endl;
	if (node != nullptr)
		RecurPrint(node->next);*/

	if (node)
	{
		//cout << *node << endl;
		RecurPrint(node->next);
		cout << *node << endl;
	}
}

void IterPrint(Node* node)
{
	// TODO:
	while (node != nullptr)
	{
		cout << *node << endl;
		node = node->next;
	}
}

int main()
{
	// ListArray와 비교

	Node* first = nullptr;
	first = new Node;
	first->item = 1;
	first->next = nullptr;

	Node* second = nullptr;
	second = new Node;
	second->item = 2;
	second->next = nullptr;

	Node* third = nullptr;
	third = new Node;
	third->item = 3;
	third->next = nullptr;

	Node* fourth = nullptr;
	fourth = new Node;
	fourth->item = 4;
	fourth->next = nullptr;

	Node* fifth = nullptr;
	fifth = new Node;
	fifth->item = 5;
	fifth->next = nullptr;

	// 계속 추가 가능

	cout << first << " " << *first << endl;
	cout << second << " " << *second << endl;
	cout << third << " " << *third << endl;
	cout << fourth << " " << *fourth << endl;
	cout << fifth << " " << *fifth << endl;
	cout << endl;

	// 연결 관계 만들어 주기
	 first->next = second;
	 second->next = third;
	 third->next = fourth;
	 fourth->next = fifth;
	 fifth->next = nullptr;
	// TODO:
	// 마지막

	cout << *(first) << endl;
	cout << *(first->next) << endl;
	cout << *(first->next->next) << endl;
	cout << *(first->next->next->next) << endl;
	cout << *(first->next->next->next->next) << endl;
	//// cout << *(first->next->next->next->next->next) << endl; // 오류

	cout << endl;

	// 임시 변수 사용
	{
		Node* current = first;
		cout << *current << endl;
		
		current = current->next;
		cout << *current << endl;

		current = current->next;
		cout << *current << endl;

		current = current->next;
		cout << *current << endl;

		current = current->next;
		cout << *current << endl;

		cout << endl;
	}

	// 재귀 호출 이용
	RecurPrint(first);
	cout << endl;

	// 반복문 이용
	IterPrint(first);
	cout << endl;

	// TODO: 데이터 삭제
	Node* current = first;

	while (current)
	{
		Node* temp = current;
		cout << "Delete" << *temp << endl;
		current = current->next;   //current를 다음으로 이동시킨 후 삭제
		delete temp;
	}

	return 0;
}