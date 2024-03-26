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
		size_t index = HashFunc(item.key); // 키를 인덱스로 사용

		if (table_[index].key != K())
			cout << "Collision!" << endl;

		// key가 int 자료형일 때 0이면 비어있는 것으로 가정
		// key가 문자열 자료형일때는 길이가 0이면 비어있는 것으로 가정
		// TODO : 비어있는 다음 공간을 찾아서 저장
		//if (table_[index].key != K())
		//{
		//	//while (table_[index].key != 0)    // 빈 곳 찾기 (int 일때)
		//	while (table_[index].key != K())    // 범용 : int에서는 0/ 문자열은 빈값 (생성자 호출)
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
		// TODO: 못 찾으면 0을 반환
		size_t index = HashFunc(key);
		for (int i = 0; i < capacity_; i++)
		{
			index = (index + i) % capacity_;
			if (table_[index].key == key)
				return table_[index].value;
		}

		return V();
	}

	// 정수 -> 해쉬값 ( key를 배열이 저장할 수 있는 인덱스로 바꿔주는 함수 : Hash Function )
	size_t HashFunc(const int& key)
	{
		// TODO:

		return key % capacity_;
	}

	// 문자열을 정수 인덱스(해쉬값)로 변환
	// Horner's method : 자릿수에 따라 g를 곱해서 더한다 -> 글자가 더해질때마다 g가 곱해지면서 앞글자에 가중치가 반영
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
	// 충돌 
	// - 개방 주소법: 선형 조사법 - 충돌 시 한칸씩 이동하며 빈곳에 저장
	// - 체이닝: 멤버 변수 Item* table_ 대신에 LinkedList<Item>* table_사용 - 충돌 해결 + 용량의 제한 없음 / link를 활용하므로 속도 측면에서는 손해

	// 키: int, 값: int 인 경우
	// 키의 범위가 아주 크고 아이템의 개수는 적을 경우
	{
		using Item = HashTable<int, int>::Item;

		HashTable<int, int> h(8);

		h.Insert(Item{ 123, 456 });

		h.Print();

		cout << "Get 123 " << h.Get(123) << endl;

		h.Insert(Item{ 1000021, 9898 });

		h.Print();

		cout << "Get 1000021 " << h.Get(1000021) << endl;

		h.Insert(Item{ 1211, 999 }); // 충돌!

		h.Print();

		cout << "Get 123 " << h.Get(123) << endl;
		cout << "Get 1211 " << h.Get(1211) << endl;
	}

	// 키: std::string, 값: int
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