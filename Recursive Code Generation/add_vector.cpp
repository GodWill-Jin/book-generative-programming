#include <iostream>
using namespace std;

// ��a+b ����> c
template<int size>
inline
void add_vectors(const double* a,const double* b, double* c)
{
	*c = *a + *b;	// ���һ��ά�ȵļ���
	return add_vectors<size - 1>(a + 1, b + 1, c + 1);
}

template<>
inline
void add_vectors<0>(const double* a, const double* b, double* c)
{ }


namespace test 
{
//TODO ����ͨ��ģ���Զ���ȡ�� ά�Ȱɣ�
void test_vector()
{
	double a[3] = {1.1	,2.2	,3.3 };
	double b[3] = {-1.0	,-2.0	,-3.0 };
	double c[3];

	add_vectors<3>(a, b, c);
}

}