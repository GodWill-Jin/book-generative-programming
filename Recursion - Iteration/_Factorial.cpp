#include "_Common.h"

//? �ݹ鷽ʽ�����ģ���ػ� ��ָ������ʱ�Ĳ�����
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
//x----------------------------------------------------------------------------------------

//? �ݹ鷽ʽ�����Stop����
struct stop
{
	enum { RET = 1 };
};

template<int n>
struct Fact
{
	using PreviousFactorial = IF<n == 0, stop, Fact<n - 1>>;
	enum
	{
		RET = (n==0)
				? PreviousFactorial::RET 
				: PreviousFactorial::RET*n	,
	};
};

//x------------------------------------------------------------------------------------

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