#include <iostream>
#include "_Common.h"
using namespace std;
/*
//x----------------------------------------------------------------
Ŀ�꣺  
	ʹ��EWHILE<> �������´��룺

				cout << 1 << endl;
				cout << 2 << endl;
				cout << 3 << endl;
				cout << 4 << endl;
				cout << 5 << endl;
				cout << 6 << endl;
				cout << 7 << endl;
				cout << 8 << endl;
				cout << 9 << endl;

//?  EWHILE< PrintCondition<10>, PrintStat<>>::exec();  
//x----------------------------------------------------------------
*/
struct STOP
{
	static void exec() {}
};

//? EWHILE<> ģ��
template<typename Condition, typename Statement>
struct EWHILE
{
	enum { isOK = Condition::template Judge<Statement>::RET };
	using Next_Statement = typename Statement::Next;

	static void exec()
	{
		// 1. call Statement if Condition OK
		//x ��ȡ���ε���Ҫ������Ŀ����䣨��Statement�У�
		IF<isOK ,Statement ,STOP>::RET::exec();

		// 2. �ݹ���� EWHILE<> if  Condition OK
		IF<isOK, EWHILE<Condition,Next_Statement>, STOP>::RET::exec();
	}
};





//x----------------------------------------------------------------
//? һ��������
template <int i_ = -1>
struct PrintStat
{
	enum { i = i_ };
	static void exec() { cout << i << endl; }
	using Next = PrintStat<i + 1>;
};

//? �����жϹ��ߣ� statement�Ƿ�������������� ����true/false
template<int n>
struct PrintCondition
{
	template<typename Statement>
	struct Judge
	{
		enum { RET = Statement::i < n };
	};
};

//?  EWHILE< PrintCondition<10>, PrintStat<>>::exec();  