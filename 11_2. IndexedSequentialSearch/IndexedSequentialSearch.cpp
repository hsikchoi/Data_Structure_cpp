#include <iostream>

using namespace std;

int SequentialSearch(int arr[], int start, int stop, int x)
{
	for (int i = start; i < stop; i++)
	{
		if (arr[i] == x)
			return i;
	}

	return -1;
}

int main()
{
	int arr[] = { 1, 2, 8, 13, 22, 45, 55, 75, 88 };
	int n = sizeof(arr) / sizeof(arr[0]);

	int keys[] = { 1, 13, 55 };
	int kn = sizeof(keys) / sizeof(keys[0]);

	int indices[] = { 0, 3, 6, n }; // �������� n �ϳ� �� �߰�

	

	for (int x : {1, 2, 8, 13, 22, 45, 55, 75, 88, 99, -1, 47, 101, 1000, 7, 10, 50, 60 })
	{
		int start = kn - 1;
		int stop = kn;

		if (x < arr[0] || x > arr[n - 1])
			cout << x << " was not found" << endl;
		else
		{
			// TODO:
			for (int i=0;i<kn;i++)
			{
				if (keys[i] > x)
				{
					start = i - 1;
					stop = i;
					break;
				}
			}
			int result = SequentialSearch(arr, indices[start], indices[stop], x);
			if (result != -1) { cout << x << " was found at " << result << endl; }
			else { cout << x << " was not found" << endl; }
		}
		
		// ���� �ؼ�
		// �ε��� ���̺��� �˻��� ���� ����
		//int k = 0;
		//while (k < kn - 1 && keys[k + 1] <= x)
		//	k++;

		// ���� ǥ�� ������ ���� ���� Ž��
		// indices[k] �̻� indices[k+1] �̸��� ���� �˻�
		// �̶� indices �迭 �������� �߰��� n�� �����صױ� ������ k+1 ��� ����
		//int found = SequentialSearch(arr, indices[k], indices[k + 1], x);
		//if (found >= 0)
		//	cout << x << " was found at " << found << endl;
		//else
		//	cout << x << " was not found" << endl;

	}

	return 0;
}