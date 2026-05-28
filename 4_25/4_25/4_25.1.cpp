#include<iostream>
using namespace std;
template<class T>
void Swap(T& left, T& right)
{
	T temp = left;
	left = right;
	right = temp;
}

template<class T>
T Add(const T& p1, const T& p2)
{
	return p1 + p2;

}

template<class T>
void Func(size_t n)
{
	T* ptr = new T[n];
	cout << ptr << '\n';
	delete[] ptr;
}

template<class T>
class Stack
{public:
	Stack(size_t n = 4)
		:_a(new T[n]),
		_top(0),
		_capacity(n){}
	void get_a()
	{
		cout<<sizeof(_a)<<endl;
	}
private:
     	T*  _a;
		size_t	_top;
		size_t _capacity;
};

int main()
{
	int a1 = 0,a2= 4;
	double m1 = 5.2, m2 = 2.5;
	Swap(a1, a2);
	Swap(m1, m2);

	cout << Add(a1, a2) << endl;
	cout << Add(m1, m2) << endl;
	Stack<int>st1(5);
	st1.get_a();
}