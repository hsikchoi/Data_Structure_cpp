#include "SparsePolynomial.h"

#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;


// ���ο� ���� �߰��� �� �ڱ� ��ġ�� ã�Ƽ� �־���� ��

// exp���� �̹� �����ϸ� �ű⿡ coef�� �����ش�.
// �������� �ʴ´ٸ� exp ���� �������� ���ĵ� ���·� ���� �߰��Ѵ�.
void SparsePolynomial::NewTerm(float coef, int exp)
{
	if (coef == 0.0f) return; // 0�̸� �߰����� ����

	if (num_terms_ >= capacity_)
	{
		// capacity ���� (num_terms�� �ϴ� ����)
		capacity_ = capacity_ > 0 ? capacity_ * 2 : 1; // 2�辿 ����
		Term* new_term = new Term[capacity_];

		// ���� ������ �ִ� ������ ����
		memcpy(new_term, terms_, sizeof(Term) * num_terms_);

		// �޸� ��ü
		if (terms_) delete[] terms_;
		terms_ = new_term;
	}

	terms_[num_terms_].coef = coef;
	terms_[num_terms_].exp = exp;

	num_terms_++;
}

float SparsePolynomial::Eval(float x)
{
	float temp = 0.0f;

	// TODO:
	for (int i = 0; i < num_terms_; i++)
	{
		temp += terms_[i].coef*std::powf(x, float(terms_[i].exp));
	}

	return temp;
}

SparsePolynomial SparsePolynomial::Add(const SparsePolynomial& poly)
{
	// this�� poly�� terms_�� exp�� ������������ ���ĵǾ� �ִٰ� ����
	// �ϳ��� ���׽� �ȿ� exp�� �ߺ��Ǵ� term�� ���ٶ�� ���� (�� exp�� �ϳ��� term�� ����)

	// ������ ��� (�޸𸮸� �� ����ϴ� ���)
	// - 1. �ִ� exp�� ã�´�.
	// - 2. �ʿ��� ũ���� Polynomial�� �����. (Sparse �ƴ�)
	// - 3. ���ϸ鼭 Polynomial�� ������Ʈ �Ѵ�. ������ �����Ǿ� �־ ����.
	// - 4. Polynomial�� SparsePolynomial�� ��ȯ�Ѵ�.

	SparsePolynomial temp;

	// TODO:
	int i = 0, j = 0;
	
	while ((i < num_terms_) && (j < poly.num_terms_))
	{
		if (terms_[i].exp == poly.terms_[j].exp)
		{
			temp.NewTerm(terms_[i].coef + poly.terms_[j].coef, poly.terms_[j].exp);
			i++;
			j++;
		}

		else if (terms_[i].exp < poly.terms_[j].exp)
		{
			temp.NewTerm(terms_[i].coef, terms_[i].exp);
			i++;
		}

		else if (terms_[i].exp > poly.terms_[j].exp)
		{
			temp.NewTerm(poly.terms_[j].coef, poly.terms_[j].exp);
			j++;
		}
	}

	//if (i==num_terms_)
		for (j; j < poly.num_terms_; j++)
		{
			temp.NewTerm(poly.terms_[j].coef, poly.terms_[j].exp);
		}
		
	//if (j == poly.num_terms_)
		for (i; i < num_terms_; i++)
		{
			temp.NewTerm(terms_[i].coef, terms_[i].exp);
		}
	return temp;
}

void SparsePolynomial::Print()
{
	bool is_first = true; // ���ϱ� ��½� Ȯ�ο�

	for (int i = 0; i < num_terms_; i++)
	{
		// 0�� �ƴ� �׵鸸 ��� ����� �ʿ䰡 ����

		if (!is_first)
			cout << " + "; // ù ���� �ƴ϶�� ���̻��̿� ���ϱ� ���

		cout << terms_[i].coef;

		if (terms_[i].exp != 0) cout << "*" << "x^" << terms_[i].exp;

		is_first = false;
	}

	cout << endl;
}