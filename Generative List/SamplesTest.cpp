#include "PtrList.h"
#include "list Generator.h"

// ����һ��Config: ��ʵ����ָ��һ��������͵�Component

struct TracedCopyMonoPersonLenListConfig
{
	using ElementType        = Person;

	using SetHeadElementType = const ElementType;
	using LengthType         = int;
	using Destoryer          = ElementDestoryer<ElementType>;
	using TypeChecker        = DynamicTypeChecker <ElementType>;
	using Copier             = MonomorphicCopier<ElementType>;

	/**
	1. Ԫ������ΪPerson�� ��Ϊ��̬�ģ�Mono-��:ֻ����һ�����͵�Ԫ��
	2. ���Ȳ���int ����
	3. ����Ԫ�صĿ�������Destory����ElementDestoryer
	4. �ṩ���ȼ�����tracing����
	*/
	using ReturnType = TracedList<
							LengthList<
								 PtrList<TracedCopyMonoPersonLenListConfig>>>;
};

using MyList = TracedCopyMonoPersonLenListConfig::ReturnType;

//X-------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	// ����ʾ��
	using Config1 = typename LIST_GENERATOR<Person, cp, poly, with_counter, with_tracing>::Config::ElementType;
	using TEST1 = typename LIST_GENERATOR<Person, cp, poly, with_counter, with_tracing>::RET;
}

