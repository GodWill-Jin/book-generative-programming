#ifndef CONT_S_H
#define CONT_S_H

namespace intimate 
{
//? ��ʹ�� ģ��ƫ�ػ� ʵ�ֵ� IF<>           ���ѳ�Աģ���װ�ڲ�ͬ��struct�У�Ȼ������ȫ�ػ�ƥ������һ��struct��
struct SelectThen
{
	template<typename ThenType,typename ElseType>
	struct Result
	{
		using RET = ThenType;
	};
};

struct SelectElse
{
	template<typename ThenType,typename ElseType>
	struct Result
	{
		using RET = ElseType;
	};
};
/*****************************************************/
template<bool Condition>
struct ChooseSelector
{
	using RET = SelectThen;
};
template<>
struct ChooseSelector<false>
{
	using RET = SelectElse;
};
/*****************************************************/
template<bool Condition,typename ThenType, typename ElseType>
class IF
{
	using selector = typename ChooseSelector<Condition>::RET;
public:
	using RET = typename selector::template Result<ThenType, ElseType>::RET;
};


}
#endif

