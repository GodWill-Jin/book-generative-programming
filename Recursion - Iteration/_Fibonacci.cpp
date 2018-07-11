
// ��̬���룺����Fibonacci��
//X ȱ�㣺����һ�� fib(k)�����˶�ε��ü���

int fib(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	return fib(n - 1) + fib(n - 2);
}


//x----------------------------------------------------------------------------------------
//x----------------------------------------------------------------------------------------
//x----------------------------------------------------------------------------------------
// ��������ʱ�临�Ӷȵĵݹ�ʵ��
int fib_(int n)  //? ���
{
	int i = 1;
	int x = 1, y = 0; // x��y�ֱ��������� fi,  f i-1

	while (i<n) {
		i = i + 1;
		x = x + y; // fk+1 = fk + fk-1
		y = x - y;
	}
	return x;
}

//? ��TM���� β�ݹ��Ż����� (tail recursion optimization)
//? ����һ�εݹ��״̬�������������ݸ���һ���ݹ飬�Ӷ�����Ҫһֱ������һ���ݹ��ջ
template<bool Condition,     // ѭ���ļ�������
		int n,				 // ѭ���Ĳ���
		int i, int x, int y> // ѭ�������е�״̬: ��ǰ���ڵ��±ꡢ��ǰ���
struct Fib_
{
	enum
	{
		RET = Fib_<(i+1<n), n, i+1, x+y, x>::RET	
	};
};
//x Fib_<>��ƫ�ػ��� ConditionΪfalseʱ
template< int n,
		  int i, int x, int y>
struct Fib_<false,n,i,x,y>
{
	enum { RET = x };
};
//************************ ����ΪFib����ĸ���Ԫ������ 
template<int n>
struct Fib
{
	enum
	{
		RET = Fib_<(n>1), n, 1,1,0 >::RET
	};
};
