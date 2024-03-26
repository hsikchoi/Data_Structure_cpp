#include <iostream>
#include "../shared/Queue.h"

using namespace std;

bool CheckSorted(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;
}

void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

int GetMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

int main()
{
	int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
	int n = sizeof(arr) / sizeof(arr[0]);

	Print(arr, n);

	Queue<int> queues[10];

	int m = GetMax(arr, n); // ���� ū �ڸ����� ã�� ���ؼ�

	for (int exp = 1; m / exp > 0; exp *= 10)
	{
		// TODO:
		for (int i = 0; i < n; i++)
		{
			queues[(arr[i] % (exp * 10))/exp].Enqueue(arr[i]);
		}

		int cnt = 0;

		

		for (int i = 0; i < n; i++)
		{
			while (!queues[i].IsEmpty())
			{
				arr[cnt] = queues[i].Front();
				queues[i].Dequeue();
				cnt++;
			}
		}



		Print(arr, n);
	}

	return 0;
}