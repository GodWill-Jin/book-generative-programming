
//? ���Լ���pow = m^n�� EWHILE
//X ����һ��Env���������״̬         > exec(Env&) �� ��������ʵ�ַḻ�ĵ���������


#include "../Hello World/_Common.h"

struct PowEnv
{
	int m, r;
	PowEnv(const int& m_,const int& r_):m(m_),r(r_){}
};


//? Bean: Statement : һ�εݹ�ʱ���������� 
//X ��һ�εݹ����ڵ� ״̬��Ϣ������Next���屾�εݹ�ļ���.
template<int n_, int i_>
struct PowStat
{
	enum
	{
		n = n_,
		i = i_
	};
	using Next = PowStat<n, i + 1>;

	static void exec(PowEnv& env) { env.r *= env.m; };
};

struct PowCond
{
	template<typename Statement>
	struct Judge
	{
		enum { RET = Statement::i < Statement::n };
	};
};
//x------------------------------------------------------------------------------
namespace intimate 
{
	struct STOP
	{
		template<typename Env>
		static void exec(Env&) {};
	};
}

template<typename Condition,typename Statement>
struct EWHILE1
{
	// �жϣ���ǰ״̬�Ƿ�Ҫexec()
	enum { judged = Condition::template Judge<Statement>::RET };

	template<typename Env>
	static void exec(Env& env)
	{
		// ��ɵ�ǰStatement: ��Ҫexec()����exec()�� ����stop()
		IF<judged,
			Statement,
			intimate::STOP>	::RET::exec(env);
		// ������һ�εݹ�
		IF<judged,
			EWHILE1<Condition, typename Statement::Next>,
			intimate::STOP>	::RET::exec(env);
	}
};


//x------------------------------------------------------------------------------
//x ʵ��Pow
template<int n>
struct PowerD1
{
	static int exec(const int& m)
	{
		PowEnv env(m, 1);
		EWHILE1<PowCond, PowStat<n, 0>>	::exec(env);  //X �������������������ֵ:n��
		return env.r;
	}
};

//? ------------------------------------------------------------------------------
void test_ewhile1()
{
	// ���� 2^3
	PowerD1<3>::exec(2);
}