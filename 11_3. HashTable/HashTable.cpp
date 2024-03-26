#include <iostream>
#include <string> // std::string

using namespace std;

template<typename K, typename V>
class HashTable
{
public:
	struct Item
	{
		K key = K();
		V value = V();
	};

	HashTable(const int& cap = 8)
	{
		capacity_ = cap;
		table_ = new Item[capacity_];
	}

	~HashTable()
	{
		delete[] table_;
	}

	void Insert(const Item& item)
	{
		size_t index = HashFunc(item.key); // Ű�� �ε����� ���

		if (table_[index].key != K())
			cout << "Collision!" << endl;

		// key�� int �ڷ����� �� 0�̸� ����ִ� ������ ����
		// key�� ���ڿ� �ڷ����϶��� ���̰� 0�̸� ����ִ� ������ ����
		// TODO : ����ִ� ���� ������ ã�Ƽ� ����
		//if (table_[index].key != K())
		//{
		//	//while (table_[index].key != 0)    // �� �� ã�� (int �϶�)
		//	while (table_[index].key != K())    // ���� : int������ 0/ ���ڿ��� �� (������ ȣ��)
		//		index++;
		//}
		//table_[index] = item;

		for (int i = 0; i < capacity_; i++)
		{
			index = (index + i) % capacity_;
			if (table_[index].key == K())
			{
				table_[index] = item;
				return;
			}
		}

		cout << "Failed to Insert" << endl;
	}

	V Get(const K& key)
	{
		// TODO: �� ã���� 0�� ��ȯ
		size_t index = HashFunc(key);
		for (int i = 0; i < capacity_; i++)
		{
			index = (index + i) % capacity_;
			if (table_[index].key == key)
				return table_[index].value;
		}

		return V();
	}

	// ���� -> �ؽ��� ( key�� �迭�� ������ �� �ִ� �ε����� �ٲ��ִ� �Լ� : Hash Function )
	size_t HashFunc(const int& key)
	{
		// TODO:

		return key % capacity_;
	}

	// ���ڿ��� ���� �ε���(�ؽ���)�� ��ȯ
	// Horner's method : �ڸ����� ���� g�� ���ؼ� ���Ѵ� -> ���ڰ� ������������ g�� �������鼭 �ձ��ڿ� ����ġ�� �ݿ�
	size_t HashFunc(const string& s)
	{
		int g = 31;
		size_t index = 0;
		for (int i = 0; i < s.size(); i++)
			index = g * index + int(s.at(i));

		return index % capacity_;
	}

	void Print()
	{
		for (int i = 0; i < capacity_; i++)
			cout << i << " : " << table_[i].key << " " << table_[i].value << endl;
		cout << endl;
	}

private:
	Item* table_ = nullptr;
	int capacity_ = 0;
};

int main()
{
	// �浹 
	// - ���� �ּҹ�: ���� ����� - �浹 �� ��ĭ�� �̵��ϸ� ����� ����
	// - ü�̴�: ��� ���� Item* table_ ��ſ� LinkedList<Item>* table_��� - �浹 �ذ� + �뷮�� ���� ���� / link�� Ȱ���ϹǷ� �ӵ� ���鿡���� ����

	// Ű: int, ��: int �� ���
	// Ű�� ������ ���� ũ�� �������� ������ ���� ���
	{
		using Item = HashTable<int, int>::Item;

		HashTable<int, int> h(8);

		h.Insert(Item{ 123, 456 });

		h.Print();

		cout << "Get 123 " << h.Get(123) << endl;

		h.Insert(Item{ 1000021, 9898 });

		h.Print();

		cout << "Get 1000021 " << h.Get(1000021) << endl;

		h.Insert(Item{ 1211, 999 }); // �浹!

		h.Print();

		cout << "Get 123 " << h.Get(123) << endl;
		cout << "Get 1211 " << h.Get(1211) << endl;
	}

	// Ű: std::string, ��: int
	{
		using Item = HashTable<string, int>::Item;

		HashTable<string, int> h(8);

		h.Insert(Item{ "apple", 1 });
		h.Insert(Item{ "orange", 2 });
		h.Insert(Item{ "mandarin", 4 });

		h.Print();

		cout << "apple " << h.Get("apple") << endl;
		cout << "orange " << h.Get("orange") << endl;
		cout << endl;

		h.Print();

		h.Insert(Item{ "tomato", 4 });

		h.Print(); 

		cout << "apple " << h.Get("apple") << endl;
		cout << "orange " << h.Get("orange") << endl;
		cout << "pineapple " << h.Get("pineapple") << endl;
		cout << endl;
	}

	return 0;
}