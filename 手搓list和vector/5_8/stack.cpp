#include<iostream>
#include<deque>
using namespace std;
template<class T,class Container=deque<T>>
class Mystack
{
private:
	Container _con;
public:
	void push(const T& val)
	{
		_con.push_back(val);
	}

	void pop()
	{
		assert(!empty());
		_con.pop_back();
	}

	T& top()
	{
		assert(!empty());
		return _con.back();
	}

	bool empty() const
	{
		return _con.empty();
	}

	size_t size()
	{
		return _con.size();
	}



};


template<class T, class Container = deque<T>>
class MyQueue
{
private:
	Container _con;
public:
	// 队尾入队
	void push(const T& val)
	{
		_con.push_back(val);
	}

	// 队头出队
	void pop()
	{
		assert(!empty());
		_con.pop_front();
	}

	// 取队首
	T& front()
	{
		assert(!empty());
		return _con.front();
	}

	// 取队尾
	T& back()
	{
		assert(!empty());
		return _con.back();
	}

	bool empty() const
	{
		return _con.empty();
	}

	size_t size() const
	{
		return _con.size();
	}
};