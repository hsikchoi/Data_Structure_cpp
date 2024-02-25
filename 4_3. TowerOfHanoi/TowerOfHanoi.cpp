#include <iostream>

#include "../shared/Stack.h"

using namespace std;

Stack<char> tower[3];

void PrintTowers()
{
	cout << "Towers" << endl;
	cout << "0: ";
	tower[0].Print();
	cout << "1: ";
	tower[1].Print();
	cout << "2: ";
	tower[2].Print();
}

// ������ ��ũ�� �������� ���õ��� ������Ʈ
void MoveDisk(int from, int to)
{
	if (tower[from].IsEmpty())
	{
		cout << "Tower " << from << " is empty." << endl;
		exit(0); // ���� ���� ����
	}

	auto disk = tower[from].Top();

	// ���� Ÿ���� ��� ������ ������ ���� �� ����
	// ���ĺ� �������� ���� �� ���� (���� X)
	if (!tower[to].IsEmpty() && tower[to].Top() > disk)
	{
		cout << "Cannot place " << disk << " on " << tower[to].Top() << endl;
		exit(0); // ���� ���� ����
	}

	tower[from].Pop();
	tower[to].Push(disk);

	cout << "Move disk " << disk << " from " << from << " to " << to << endl;
	PrintTowers();
}

void RecurMoveDisks(int n, int from, int temp, int to)
{
	// TODO:

	if (n == 0)
		return;

	RecurMoveDisks(n - 1, from, to, temp);

	MoveDisk(from, to);
	
	RecurMoveDisks(n - 1, temp, from, to);

}

int main()
{
	int num_disks = 4;

	for (int i = 0; i < num_disks; i++)
		tower[0].Push('A' + i);

	PrintTowers();

	//MoveDisk(0, 2); // <- ��ũ �ϳ��� �����̴� �Լ� tower 0 -> tower 2

	RecurMoveDisks(num_disks, 0, 1, 2);

	return 0;
}