
template<typename ElemType_, int size_>
class Vector
{
public:
	typedef ElemType_ element_type;
	enum { size = size_ };

private:
	element_type elems[size];
};

//? ö�٣��������״
enum MatrixShapes
{
	rectangle,
	square,
	diagonal,
	lower_triang,
	upper_triang
};

class Diagonal_10x10_MatrixOf_Doubles
{
public:
	//? traits class
	struct Config
	{
		typedef double ElemType;
		enum
		{
			rows = 10,
			cols = 10,
			shape = diagonal
		};
	};

	double at(int x, int y);
};

//? ������Ϣ��ģ�壬�����͵�default��Ϣֵ
template <typename T>
class numeric_limits
{
public:
	static const bool is_specialized = false; // �Ƿ����ػ�
	static const bool has_denorm = false; // �Ƿ��з�������ʾ
	static const bool has_infinity = false; // �Ƿ��ȡ����
	static const bool is_integer = false; // �Ƿ�Ϊ����

	static const int digit10 = 0; // ʮ���Ƶ����ֵ

	static T min() throw();

};

//? �ػ���һ���ض����͵�������Ϣ
template<>
class numeric_limits<float>
{
	static const bool is_specialized = true; // �Ƿ����ػ�
	static const bool has_denorm = false; // �Ƿ��з�������ʾ
	static const bool has_infinity = false; // �Ƿ��ȡ����
	static const bool is_integer = false; // �Ƿ�Ϊ����

	static const int digit10 = 6; // ʮ���Ƶ����ֵ

	static float min() throw() { return 1.175435E-38F; }
};