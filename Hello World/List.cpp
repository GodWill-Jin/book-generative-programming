#include "_Common.h"

#include <iostream>
using namespace std;

//?  ͳһ��using �������ͱ����� ����ǰ���ͳһ������

/*
//X ������ģ��Ĺ����൱�ں�����
//x             ��ô���з���ֵRET: �����Ƿ���һ���������ͣ���Ҳ�����Ƿ���һ��ֵ��enumerator��
//x               ��ʹ�����ģ��ʱ��������� ::RET  !(������ص������ͣ���Ҫ��typenmae)
*/
/***************************************************************/
/*
//? ����  1-> 2 ->3
����ʽд����  cons(1, cons(2, cons(3 nail) ) )   
ģ��Ԫд����  Cons<1, Cons<2, Cons<3, End> > >

ÿ���ڵ�ʱһ��ʵ�������ͣ��� head��ֵ��tailָ����һ��ʵ�������ͣ�
*/

const int endValue = ~(~0u >> 1); // int����Сֵ��λ����ʵ�֣�

// ֵhead,��һ������ʵ��tail
struct End
{
	enum
	{
		head = endValue
	};
	typedef End tail;
};

template<int head_, typename tail_ = End >
struct Cons
{
	enum
	{
		head = head_
	};
	typedef tail_ tail;
};
/***************************************************************/
//? Length()
template<typename List>
struct Length
{
	enum
	{
		RET = 1 + Length<typename List::tail>::RET
	};
};

template<>
struct Length<End>
{
	enum { RET = 0};
};
/***************************************************************/
//? Append() �� һ��Ԫ�ؽڵ�
template<typename List, int n>
struct AppendL
{
	using RET = Cons<List::head, 
					typename AppendL<typename List::tail, n>::RET
					>	;
};

template<int n>
struct AppendL<End, n>
{
	using RET = Cons<n>;
};
/***************************************************************/
//? Aped():  һ��list
template<typename list1, typename list2>
struct Aped
{
	using RET = Cons<list1::head,
					typename Aped<typename list1::tail, list2>::RET
						>;
};

//x							 template <typename list1, typename list2>
template<typename list2> //x �ػ�һ��ģ��ʱ����ָ����ģ������Ͳ�����д�ˣ���Ϊ�Ѿ�û������ɱ��ģ������ˣ�������
struct Aped<End, list2>
{
	using RET = list2;
};

/***************************************************************/
//? isEmpty()
template<typename list>
struct IsEmpty
{
	enum
	{
		RET = list::head == endValue	,
	};
};

/***************************************************************/
//? Last()
template<typename list>
struct Last
{
	enum { val = list::head };		//x ֻ�ܱȽ�����ֵ��ò��û���Ƚ����������Ƿ���ͬ������
	/*
	using RET = (val == endValue) ? list
								 : Last<typename list::tail>::RET;
	*/
	using RET = IF<val == endValue,
					list,
					typename Last<typename list::tail>::RET>;
};

/***************************************************************/
void main_3()
{
	typedef Cons<1, Cons<2, Cons<3>>> list1;
	cout << Length<list1>::RET;
	cout << Length< AppendL<list1, 4>::RET >::RET;

	typedef Cons<7, Cons<8, Cons<9>>> list2;
	cout << Length< Aped<list1, list2>::RET >::RET;
}
