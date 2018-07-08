#include <iostream>

using namespace std;

/*
//x RET ���Ǹ�Ԫ������ ����ֵ:
		������������ �������� ���ţ�������������ݣ�һ������ֵ/ һ������
		������ģ����������������ͣ���RETT�� typedef ���ġ��������ʵġ� ����
		������ģ��������Ǽ���ֵ��  ��RETV�� enum �ж���ġ�ֵ���ʵġ�  ����

//x һ��template�ࣺ�ɵ���һ����������
		һ��������ʽ enumulator RET = f(x,y,z)��
//x һ��template�ࣺҲ�ɵ���һ����Class�� ������һ��ʵ�� Temp<x,y> ���൱��һ������status value�� ����
*/
/***************************************************************/
//? if-else
template <bool Condition,typename Then, typename Else>
struct  IF
{
	typedef Then RET;
};

template <typename Then, typename Else>
struct  IF<false,Then,Else>
{
	typedef Else RET;
};

/***************************************************************/
//? switch-case
template <int default_Case> 
struct CaseActions
{
	enum
	{
		RET = 0, // ����Case��action
	};
};

template <> 
struct CaseActions<1>
{
	enum
	{
		RET = 111, // ����Case��action
	};
};

template <> 
struct CaseActions<2>
{
	enum
	{
		RET = 222, // ����Case��action
	};
};

template <int Condition_val>
struct SWITCH
{
	enum
	{
		RET = CaseActions<Condition_val>::RET
	};
};
/***************************************************************/
//? ���� Factorial<n>::RET   =  n!
template<int n>
struct Factorial
{
	enum
	{
		RET = Factorial<n-1>::RET*n
	};
};

template<>
struct Factorial<0>
{
	enum
	{
		RET = 1
	};
};

//? C(k,n) = n! / k!(n-k)!  ��n�������k������������Ƶ�ʱ�쳣ֱ�ӿ�����������
template<int k,int n>
class Combinations
{
private:
	enum
	{
		num = Factorial<n>::RET,
		denum = Factorial<k>::RET * Factorial<n-k>::RET
	};
public:
	enum
	{
		RET = num/ denum
	};
};

/***************************************************************/
//x template class��Ȼ�ǿ��԰���ֵ״̬�ģ������Լ���ÿ��ʵ�������Ե���instance����
//x ���Ҷ����˺�����������������ģ��ʵ���ͳ���һ����������


//? ������
template <int mantissa_, int exp_>
struct Float
{
	enum
	{
		mantissa = mantissa_,
		exp = exp_
	};
	operator const float() const {
		return mantissa_ * pow(10, exp_);
	}

	static const float v = Float<mantissa_, exp_>();
};

/***************************************************************/
//? Sqrt()
template<typename Float>
struct Sqrt
{
	enum
	{
		val = sqrtf(Float()),
	};

	typedef Float<val,0> RET;
};
/***************************************************************/

//x***************************************************************

int main(int argc, char* argv[])
{
	cout << Factorial<10>::RET << endl;

	IF<(1 + 2 > 4), short, int>::RET i;

	cout << Combinations<3,10>::RET << endl;

	cout << SWITCH<555>::RET << endl;
	cout << SWITCH<1>::RET << endl;
	cout << SWITCH<2>::RET << endl;

	typedef Float<25, -1> F2p5;
	float v3 = 8.0;
	static const float v0 = v3 + F2p5();
	typedef typename Sqrt<F2p5>::RET RESULT;
	static const int v1 = 8 + RESULT();
	cout << v0 << v1;

}

const int v5 = 8.0 + Float<25, -1>::v;
