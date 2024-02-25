#include "MyString.h"

using namespace std;

// ��� �ִ� MyString() ����

MyString::MyString()
{
	str_ = nullptr;
	size_ = 0;
}

// �� �ڿ� �� ĳ����'\0'�� ��� �ִ� ���ڿ��κ��� �ʱ�ȭ
MyString::MyString(const char* init)
{
	// ũ��(size_) ����
	size_ = strlen(init);

	//�ٸ����
	/*
	size_ = 0;
	while (init[size_] != '\0')
		size_++;
	*/

	// �޸� �Ҵ�
	str_ = new char[size_];
	// ������ ����
	memcpy(str_, init, size_);
}

// MyString�� �ٸ� instance�κ��� �ʱ�ȭ
MyString::MyString(const MyString& str)
{
	// �⺻ ���� �����ڴ� ������ �ּҸ� �����ϱ� ������ 
	// �Ҹ�� ���� �߻�
	// ���⼭�� ���� �޸𸮸� �Ҵ� �޾Ƽ� ����
	size_ = str.size_;
	str_ = new char[size_];
	memcpy(str_, str.str_, size_);
}

MyString::~MyString()
{
	// �޸� ����
	if (str_ != nullptr)
	{
		delete[] str_;
		// ���ϴ� ���� ����
		str_ = nullptr;
		size_ = 0;
	}
}

bool MyString::IsEmpty()
{
	return Length() == 0;
}

bool MyString::IsEqual(const MyString& str) // ���ǻ� ����& ���
{
	// ��Ʈ: str.str_, str.size_ ����
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
	// �޸� ���Ҵ�� ���� ���� �ִ� ���� ����
	
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

// �ε��� start��ġ�� ���ں��� num���� ���ڷ� ���ο� ���ڿ� �����
MyString MyString::Substr(int start, int num)
{
	// ������ �ε���: start, start + 1, ... , start + num - 1
	assert(start + num - 1 < this->size_); // ������ �ܼ��ϰ� ����� ���� ����

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

	//�ٸ����
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

		// �� ���� �˰��� : Knuth-Morris-Pratt
	}
}
*/


void MyString::Print()
{
	for (int i = 0; i < size_; i++)
		cout << str_[i];
	cout << endl;
}