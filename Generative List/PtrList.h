#ifndef PRTLIST_H
#define PRTLIST_H

#include <cassert>
#include <iostream>

struct Person;

/*
�����������ڶ�������
������ģ�壬�����һ�����ֻ�ܳ���һ�������ʵ�֡�
��Ȼ���������Interface? ��ʵ�ֶ�̬������
���ߣ��ѱ��������������ģ������Ͳ�����
*/
template<typename Generator>
class PtrList
{
public:
	// ʹConfig_��Ϊmember type
	using Config = typename Generator::Config;
private:
	// retrieve needed types from config repository
	using ElementType = typename Config::ElementType;
	using SetHeadElementType = typename Config::SetHeadElementType;
	using ReturnType = typename Config::ReturnType;
	using Destoryer = typename Config::Destoryer;
	using TypeChecker = typename Config::TypeChecker;
	using Copier = typename Config::Copier;

public:
	PtrList(SetHeadElementType& h, ReturnType* t= nullptr):
		head_(nullptr),tail_(t)
	{ setHead(h); }

	~PtrList() { Destoryer::destory(head_); }

	void setHead(SetHeadElementType& h)
	{
		TypeChecker::check(h);
		head_ = Copier::copy(h);
	}

	void setTail(ReturnType* t) { tail_ = t; }

	ElementType& head(){ return *head_; }

	ReturnType* tail(){ return tail_; }

private:
	ElementType* head_;
	ReturnType* tail_;
};

//X ============================================================================
//? ���������
// �����������Ԫ�صĿ���/�������ã����ô�������
template<typename ElementType>
struct ElementDestoryer
{
	static void destory(ElementType* e) { delete e; }
};

// ����Elements�ĳ����ǡ�external reference��
template<typename ElementType>
struct EmptyDestoryer
{
	static void destory(ElementType* e) { }
};
//X ============================================================================
//? TypeChecker
template<typename ElementType>
struct DynamicTypeChecker
{
	static void check(ElementType& e)
	{
		assert(	typeid(e) == typeid(ElementType) );
	}
};

template<typename ElementType>
struct EmptyTypeChecker
{
	static void check(ElementType& e){ }
};
//X ============================================================================
//? ��������Copier
template<typename ElementType>
struct PolymorphicCopier
{
	static ElementType* copy(ElementType& e) { return e->clone(); }
};

template<typename ElementType>
struct MonomorphicCopier
{
	static ElementType* copy(ElementType& e) { return new ElementType(e); }
};

template<typename ElementType>
struct EmptyCopier
{
	static ElementType* copy(ElementType& e) { return &e; }
};
//X ============================================================================
template<typename BaseList>
class LengthList: public BaseList
{
public:
	using Config = typename BaseList::Config;

private:
	using ElementType = typename Config::ElementType;
	using SetHeadElementType = typename Config::SetHeadElementType;
	using ReturnType = typename Config::ReturnType;
	using LengthType = typename Config::LengthType;

public:
	LengthList(SetHeadElementType& h, ReturnType* t=nullptr):
		BaseList(h,t),length_(computedLength())
	{ }

	void setTail(ReturnType* t)
	{
		BaseList::setTail(t);
		length_ = computedLength();
	}

	const LengthType& length() const
	{
		return length_;
	}

private:
	LengthType computedLength() const
	{
		return BaseList::tail() ? BaseList::tail()->Length + 1 : 1;
	}

	LengthType length_;
};

//X ============================================================================
template<typename BaseList>
class TracedList: public BaseList
{
public:
	using Config = typename BaseList::Config;
private:
	using ElementType = typename Config::ElementType;
	using SetHeadElementType = typename Config::SetHeadElementType;
	using ReturnType = typename Config::ReturnType;

public:
	TracedList(SetHeadElementType& h, ReturnType* t = nullptr):
		BaseList(h,t)
	{ }

	void setHead(SetHeadElementType& h)
	{
		std::cout << "setHead(" << h << ")" << std::endl;
		BaseList::setHead(h);
	}

	ElementType& head()
	{
		std::cout << "head()" << std::endl;
		return BaseList::head();
	}

	void setTail(ReturnType* t)
	{
		std::cout << "setTail(t)" << std::endl;
		BaseList::setTail(t);
	}
		
};

#endif

