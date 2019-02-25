#include "account.h"

//? ����͸֧���˻�
//x �޸�debit()�ÿ������Ϊ
template<typename Base>
class NoCredit : public Base
{
public: // ȡ����ʹ�õ�Component
	using Config = typename Base::Config;
	using Owner = typename Base::Owner;
	using NumericType = typename Base::NumericType;

	NoCredit(const Owner& own):Base(own){ }

	// @override
	void debit(const NumericType& amount)
	{
		assert(amount > 0);
		if (Base::balance()-amount<0) {
			throw "No credit Available!";
		}else {
			Base::debit(amount);
		}
	}
};

//X------------------------------------------------------------------------
//? ��͸֧���˻�����͸֧�������ƣ�
//x ����limit(͸֧�޶�)��Ա�� ��дdebit()��Ϊ
template<typename Base>
class Credit: public Base
{
public: // ȡ����ʹ�õ�Component
	using Config = typename Base::Config;
	using Owner = typename Base::Owner;
	using NumericType = typename Base::NumericType;

	Credit(Owner& own):Base(own),limit_(0){ }

	NumericType& limit() const { return limit_; } //TODO ֻ������ �ܷ��� ���Ա�ķ�const���� ������
	void limit(const NumericType& newLimit) { limit_ = newLimit; }

	// @override
	void debit(const NumericType& amount)
	{
		assert(amount > 0);
		if (Base::balance()-amount< -limit_) {
			throw "Account overdrawn!";
		}else {
			Base::debit(amount);
		}
	}
private:
	NumericType limit_;
};

