#include "MyString.h"

using namespace std;

// 비어 있는 MyString() 생성

MyString::MyString()
{
	str_ = nullptr;
	size_ = 0;
}

// 맨 뒤에 널 캐릭터'\0'가 들어 있는 문자열로부터 초기화
MyString::MyString(const char* init)
{
	// 크기(size_) 결정
	size_ = strlen(init);

	//다른방법
	/*
	size_ = 0;
	while (init[size_] != '\0')
		size_++;
	*/

	// 메모리 할당
	str_ = new char[size_];
	// 데이터 복사
	memcpy(str_, init, size_);
}

// MyString의 다른 instance로부터 초기화
MyString::MyString(const MyString& str)
{
	// 기본 복사 생성자는 포인터 주소만 복사하기 때문에 
	// 소멸시 오류 발생
	// 여기서는 새로 메모리를 할당 받아서 복사
	size_ = str.size_;
	str_ = new char[size_];
	memcpy(str_, str.str_, size_);
}

MyString::~MyString()
{
	// 메모리 해제
	if (str_ != nullptr)
	{
		delete[] str_;
		// 이하는 생략 가능
		str_ = nullptr;
		size_ = 0;
	}
}

bool MyString::IsEmpty()
{
	return Length() == 0;
}

bool MyString::IsEqual(const MyString& str) // 편의상 참조& 사용
{
	// 힌트: str.str_, str.size_ 가능
	if (size_ == str.size_)
	{
		for (int i = 0; i < size_; i++)
		{
			if (str_[i]!=str.str_[i])
			{break;}
		}
		return true;
	}

	return false;
}

int MyString::Length()
{
	return size_;
}

void MyString::Resize(int new_size)
{
	// 메모리 재할당과 원래 갖고 있던 내용 복사
	
	char *new_str = new char[new_size];


	for (int i = 0; i < (new_size < size_ ? new_size : size_); i++)
	{
		new_str[i] = str_[i];
	}

	memcpy(new_str, str_, new_size);

	delete[] str_;
	str_ = new_str;
	size_ = new_size;

	/*
	if (new_size != size_)
	{
		char* new_str = new char[new_size];

		for (int i = 0; i < (new_size < size_ ? new_size : size_); i++)
			new_str[i] = str_[i];

		delete[] str_;
		str_ = new_str;
		size_ = new_size;
	}
	*/
}

// 인덱스 start위치의 글자부터 num개의 글자로 새로운 문자열 만들기
MyString MyString::Substr(int start, int num)
{
	// 복사할 인덱스: start, start + 1, ... , start + num - 1
	assert(start + num - 1 < this->size_); // 문제를 단순하게 만들기 위해 가정

	MyString temp;
	
	// TODO:
	temp.size_ = num;
	temp.str_ = new char[temp.size_];

	for (int i = 0; i < temp.size_; i++)
	{
		temp.str_[i] = str_[i + start];
	}

	

	return temp;
}

MyString MyString::Concat(MyString app_str)
{
	MyString temp;

	// TODO:
	temp.size_ = size_ + app_str.size_;
	temp.str_ = new char[temp.size_];

	for (int i = 0; i < size_; i++)
	{temp.str_[i] = str_[i];}
	for (int i = size_; i < size_ + app_str.size_; i++)
	{temp.str_[i] = app_str.str_[i - size_];}

	//다른방법
	/*
	memcpy(temp.str_, this->str_, this->size_);
	memcpy(&temp.str_[this->size_], app_str.str_, app_str.size_);
	*/
	return temp;
}

MyString MyString::Insert(MyString t, int start)
{
	assert(start >= 0);
	assert(start <= this->size_);

	MyString temp;

	// TODO:
	temp.size_ = size_ + t.size_;
	temp.str_ = new char[temp.size_];

	memcpy(temp.str_, str_, size_);

	for (int i = 0; i < start; i++)
	{
		temp.str_[i] = str_[i];
	}

	for (int i = start; i < start + t.size_; i++)
	{
		temp.str_[i] = t.str_[i - start];
	}

	for (int i = start + t.size_; i < temp.size_; i++)
	{
		temp.str_[i] = str_[i - t.size_];
	}
	

	return temp;
}

int MyString::Find(MyString pat)
{
	int lencnt = 0;
	//TODO:
	for (int i = 0; i < size_+1; i++)
	{
		if (lencnt == pat.size_)
		{return i - pat.size_;}

		if (str_[i] == pat.str_[lencnt])
		{lencnt++;}

		else
		{lencnt = 0;}
	}

	return -1;
}

/*
int MyString::Find(MyString pat)
{
	for (int start = 0; start <= Length() - pat.Length(); start++)
	{
		//check for match beginning at str_[start]
		int j;
		for (j = 0; j < pat.Length() && str_[start + j] == pat.str_[j]; j++)
		{
			if (j == pat.Length() - 1)
				return start;    // match found
			// no match at position start
		}
		return -1;   // pat is empty or does not occur

		// 더 빠른 알고리즘 : Knuth-Morris-Pratt
	}
}
*/


void MyString::Print()
{
	for (int i = 0; i < size_; i++)
		cout << str_[i];
	cout << endl;
}