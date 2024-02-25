#include "../shared/Queue.h"

#include <iostream>

using namespace std;

int main()
{
	int n = 5, k = 2; // set n and k to the desired values

	Queue<int> q(n + 1);
	q.SetDebugFlag(false);

	// ó���� n�� �߰� (1, 2, ..., n)
	for (int i = 1; i <= n; i++)
		q.Enqueue(i);
	q.Print();

	// ������ �� ���� ���� ������ �ݺ�
	while (q.Size() != 1)
	{
		// k-1 ���� �� �տ��� �ڷ� ������
		for (int i = 0; i < k - 1; i++)
		{
			int temp = q.Front();
			q.Dequeue();
			q.Enqueue(temp);
		}
		
		// k ��° ��� ó��
		cout << "Executed " << q.Front() << endl;
		q.Dequeue();
		q.Print();
	}

	// ������ ������ ��ȣ
	cout << "Survivor: " << q.Front() << endl;

	return 0;
}