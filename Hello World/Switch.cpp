#include "_Common.h"
#include <iostream>
using namespace std;
/*
switch()
{
	case1:
	case2:
	...
}
*/
//? Case�࣬��ÿ��ʵ����һ��Case
struct A {static void execute() { cout<<"A"<<endl ; } };
struct B {static void execute() { cout<<"B"<<endl ; } };
struct D {static void execute() { cout<<"Default"<<endl ; } };
struct DDD {static void execute() { cout<<"DDD"<<endl ; } };

const int DEFAULT = 100;
struct End
{
	
};

struct DefaultCase
{

}; 

/********************************************************************/
//? һ���Caseʵ��
template<int val,typename T, typename NextCase = End>
struct CASE
{
	enum
	{
		VAL = val,
	};
	using TYPE = T;
	using Next = NextCase;
};

//? default���Ǹ�caseʵ��
template<typename T, typename NextCase = End>
struct CASE<DEFAULT,T, NextCase>
{
	enum
	{
		VAL = DEFAULT,
	};
	using TYPE = T;
	using Next = DefaultCase;
};
/********************************************************************/
//? �ݹ����
template<int Condition , typename CaseList >
struct SWITCH
{
	using RET = typename IF<(Condition == CaseList::VAL),
							typename CaseList::TYPE,
							typename SWITCH<Condition, typename CaseList::Next>::RET
							>::RET;
				
};
//? �ݹ����һ���� SWITCH<  Condition, CASE<DEFAULT,D,DefaultCase>  >
//?   ��һ������ SWITCH<Condition, DefaultCase::Next>
//?   ��Ҫ�������������ʱ����дSWITCH,ֱ�ӷ��� CaseList::TYPE
template<int Condition>
struct SWITCH<Condition,CASE<DEFAULT,D,End>>
{
	using RET = DDD;
};
/********************************************************************/

void main_5()
{
	// ����
	using T00 = typename
	SWITCH<(10),
		CASE<DEFAULT, D
		>>::RET;

	using T0 = typename
	SWITCH<(10),
		CASE<10, A,
		CASE<DEFAULT, D
		>>>::RET;

	// D
	using T1 = typename
	SWITCH<(1 + 1 - 2),
		CASE<1, A,
		CASE<2, B,
		CASE<DEFAULT, D
		>>>>::RET;

	// A
	using T2 = typename
	SWITCH<(1 + 1 - 1),
		CASE<1, A,
		CASE<2, B,
		CASE<DEFAULT, D
		>>>>::RET;

	// B
	using T3 = typename
	SWITCH<(1 + 1),
		CASE<1, A,
		CASE<2, B,
		CASE<DEFAULT, D
		>>>>::RET;
}