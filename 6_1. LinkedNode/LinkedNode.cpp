#include <iostream>

using namespace std;

// sequential representation : ��ü�� Ž���ϴ� process�� ���� �� ���� / ������ ���� ������ ����� ��쿡�� ��ȿ����
// �����͸� ���� ����߷� ������ ���? ������ �ּҸ� �˸� �����͸� ã�ư� �� ����
// -> �ּҸ� �����ϴ°� �߿��� task -> �ּҸ� �Ѱ��� ������ �ᱹ �迭�� �Ǳ� ������ sequential representation�� ��
// �����Ϳ� ���� �����Ϳ� ���� ��ũ�� ���� �����Ѵ� : �����Ͱ� ����� ��� �� ���� ������+���� ��忡 ���� �����͸� �Բ� ���� -> linked representation


struct Node
{
	int item = 0;	  // <- ū �����͵� ����
	Node* next = nullptr;

	friend ostream& operator<<(ostream& os, const Node& n)
	{
		cout << "[" << &n << ", " << n.item << ", " << n.next << "]" << flush;
		return os;
	}
};

void RecurPrint(Node* node)
{
	// TODO: �޸� ���� ���� ���� �ľ�
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
	// ListArray�� ��

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

	// ��� �߰� ����

	cout << first << " " << *first << endl;
	cout << second << " " << *second << endl;
	cout << third << " " << *third << endl;
	cout << fourth << " " << *fourth << endl;
	cout << fifth << " " << *fifth << endl;
	cout << endl;

	// ���� ���� ����� �ֱ�
	 first->next = second;
	 second->next = third;
	 third->next = fourth;
	 fourth->next = fifth;
	 fifth->next = nullptr;
	// TODO:
	// ������

	cout << *(first) << endl;
	cout << *(first->next) << endl;
	cout << *(first->next->next) << endl;
	cout << *(first->next->next->next) << endl;
	cout << *(first->next->next->next->next) << endl;
	//// cout << *(first->next->next->next->next->next) << endl; // ����

	cout << endl;

	// �ӽ� ���� ���
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

	// ��� ȣ�� �̿�
	RecurPrint(first);
	cout << endl;

	// �ݺ��� �̿�
	IterPrint(first);
	cout << endl;

	// TODO: ������ ����
	Node* current = first;

	while (current)
	{
		Node* temp = current;
		cout << "Delete" << *temp << endl;
		current = current->next;   //current�� �������� �̵���Ų �� ����
		delete temp;
	}

	return 0;
}