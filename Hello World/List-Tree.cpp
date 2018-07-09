#include "_Common.h"

#include <iostream>
using namespace std;

#define EB enum{
#define EN };

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
	enum
	{
		RET = IsEmpty<typename list::tail>::RET 
							? list::head  
							: Last<typename list::tail>::RET,
	};
	using next = typename list::tail; //? ���һ���ڵ�:End�ڵ�,�� RET0ΪUnknown
	using RET0 = typename IFI <IsEmpty<next>::RET, list, typename Last<next>::RET0>::RET;
};

template<>
struct Last<End>
{
	enum { RET = 666 };
	using RET0 = End;
};

/***************************************************************/
void main_3()
{
	using list1 = Cons<1, Cons<2, Cons<3>>>;
	cout << Length<list1>::RET;
	cout << Length< AppendL<list1, 4>::RET >::RET;

	using list2 = Cons<7, Cons<8, Cons<9>>>;
	cout << Length< Aped<list1, list2>::RET >::RET;

	cout <<IsEmpty<End>::RET;
	cout <<IsEmpty<list1>::RET;

	cout << Last<list1>::RET;   // ȡ���һ���ڵ��ֵ  //TODO
	using last_of_list1 = Last<list1>::RET0;	// ȡ���һ���ڵ�

}
/***************************************************************/
template<int n>
struct Int
{
	enum{ value = n};
};
struct Endp
{
	using head = Int<endValue>;
	using Tail = Endp;
};
template <typename head_, typename tail_= Endp>
struct Conp
{
	using head = head_;
	using Tail = tail_;
};

void main_4()
{
	//?  ������
	using list1 = Conp<Int<1>,  Conp<     Conp<Int<21>,Conp<Int<31>>>  ,  Conp<Int<22>>       >>;
}



