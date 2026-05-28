//赋值运算符重载
#include<iostream>
using namespace std;

class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	//传引用返回可以减少拷贝(之前提到过在这里传值返回是自动调用拷贝函数的)
	//这里能使用是传引用返回是因为第一个参数用this来的，函数栈帧销毁也不会找不到
	//函数要返回类型是为例更好处理连续赋值的情况(d3=d1=d2)，用void不好处理
	Date& operator=(const Date& d)//const和传引用传参的作用就不再多说了
	{
		//自己等于自己就可以不用赋值了
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		//比如：d1=d2表达式的返回对象应该为d1,也就是*this
		return *this;
	}
	//赋值运算符重载，但其实在Date类型里面不写也没影响，跟拷贝构造函数处理内置类型原理一样
	//思考联想方法也一样，不再说了

	void Print()
	{
		cout << _year << "/" << _month << "/" << _day << '\n';
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1;
	Date d2(2025, 8, 1);
	d1 = d2;

	Date d3;
	d3 = d1 = d2;//从右往左

	d1.Print();
	d2.Print();
	d3.Print();

	// 需要注意这里是拷⻉构造，不是赋值重载
	// 要牢牢记住赋值重载完成两个已经存在的对象直接的拷⻉赋值
	// 而拷⻉构造用于一个对象拷⻉初始化给另⼀个要创建的对象
	Date d4 = d1;//因为拷贝构造如果写出这样就有点容易混
	//Date d4(d1);//写成这样的时候不太容易混淆

	return 0;
}