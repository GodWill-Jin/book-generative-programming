#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <ostream>
#include <cassert>
using namespace std;

template<typename Config_>
class PersonalAccount
{
public:
	using Config = Config_;
	using Owner = typename Config::Owner;
	using Currency = typename Config::Currency;
	using Date = typename Config::Date;
	using NumericType = typename Config::NumericType;
	using CounterType = typename Config::CounterType;
	using AccountNoType = typename Config::AccountNoType;

	PersonalAccount(Owner& own):
		owner_(own),balance_(0),transactions_(0)
	{ }

	// ��5��fields���ݵķ���
	const Owner& owner() { return owner_; }
	const AccountNoType& number() { return accountNo_; }
	const NumericType& balance() { return balance_; }
	const CounterType& transactions() { return transactions_; }
	const Date& openedOn() { return openedOn_; }

	const char* currency() const { return Currency::symbol(); }

	// ���(����)
	void credit(const NumericType& amount)
	{
		assert(amount > 0);
		book(amount);
	}

	// �ÿ������
	void debit(const NumericType& amount)
	{
		assert(amount > 0);
		book(-amount);
	}

protected:
	NumericType balance_;	//x ������
	CounterType transactions_;

private:
	Owner owner_;
	const AccountNoType accountNo_;
	const Date openedOn_;

	// ����
	void book(const NumericType& amount)
	{
		balance_ += amount;
		++transactions_;
	}

	// ��ֹ��¶���½ӿ�
	PersonalAccount(const PersonalAccount&) {}; // ��ֹ�˻����������Ƕ�һ�޶���
	PersonalAccount& operator =(const PersonalAccount&) { return *this; }
};

//x--------------------------------------------------------------------------
//? ����Currency
struct DEM
{
	static const char* symbol() { return "DEM"; }
};

struct EUR
{
	static const char* symbol() { return "EUR"; }
};

struct USD
{
	static const char* symbol() { return "USD"; }
};
//x--------------------------------------------------------------------------
//? �˻�������AccountNoType
class StaticNo
{
public:
	StaticNo():number_(counter_++){ }
	void print(std::ostream& os) const { os << number_; }
private:
	long int number_;
	static long int counter_;

	// ��Ϊprivate����ֹ����
	StaticNo(const StaticNo&){ }
	StaticNo& operator =(const StaticNo&) { return *this; }
};
long int StaticNo::counter_ = 0;

inline
ostream& operator <<(ostream& os,const StaticNo& staNo)
{
	staNo.print(os);
	return os;
}

//x--------------------------------------------------------------------------

#endif

