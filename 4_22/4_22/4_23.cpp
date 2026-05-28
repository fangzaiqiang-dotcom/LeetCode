//写一个函数 void reset(int& n) 将传入的整数重置为 0，并测试。

//写一个函数 int& getMax(int& a, int& b) 返回较大值的引用，并在外面修改它。


//定义一个 const 引用，尝试修改它，观察编译错误。


#include<iostream>
using namespace std;
void reset(int& n)
{
	n = 0;
}
int main()
{

	int x = 7;
	cout << x << endl;
	return 0;

}