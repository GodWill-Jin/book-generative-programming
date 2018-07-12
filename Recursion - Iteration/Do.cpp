#include "_Common.h"
#include "iostream"
using namespace std;
//X---------------------------------------------------------------------
// ����һ��״̬���󣬲��������״̬����
template<typename Stat>
struct STOP
{
	using RET = Stat;
};

template<typename Stat, typename Condition>
struct DO
{
	using NextStat = typename Stat::NextStat;
	enum
	{
		RET = IF<Condition::template Judge<Stat>::RET,
					DO<NextStat, Condition>,
					STOP<NextStat>
				>::RET::RET	,
	};
};

//X---------------------------------------------------------------------
namespace dynamic_code 
{
// ����һ��������ƽ��������������
int sqrt(int n)
{
	int p = -1;
	do {
		p += 2;
		n -= p;
	} while (n>=0);
	return p/2 ;
}
}
//X---------------------------------------------------------------------
template<int n_,int p_>
struct SqrtStat
{
	enum
	{
		p = p_,
		n = n_
	};
	using NextStat = SqrtStat<n-p-2, p+2>;
};

struct SqrtCondition
{
	template<typename Stat>
	struct Judge
	{
		enum { RET = Stat::n >= 0 };
	};
};

template<int n>
struct Sqrt
{
	enum
	{
		p = DO< SqrtStat<n, -1>, SqrtCondition >::RET::p
	};
};










