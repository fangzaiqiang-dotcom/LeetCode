#include<iostream>
#include <cassert>
template<class T>
class MyPriorityQueue
{
private:
	T* _arr;
	size_t _capacity;
	size_t _size;

	void expand()
	{
		if (_size == _capacity)
		{
			size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
			T* tmp = new T[newcapacity];
			for (size_t i = 0;i < _size;i++)
			{
				tmp[i] = _arr[i];
			}
			delete[] _arr;
			_arr = tmp;
			_capacity = newcapacity;
		}
	}

	void adjustUp(size_t child)
	{
		while (child > 0)
		{
			size_t  parent = (child - 1) / 2;
			if (_arr[child] > _arr[parent])
			{
				std::swap(_arr[child], _arr[parent]);
				child = parent;
			}
		    else
			{
				break;
			}
	     }
	}
	
	void adjustDown(size_t parent)
	{
		size_t child = parent * 2 + 1;
		while (child < _size)
		{
			if (child + 1 < _size && _arr[child] < _arr[child + 1])
				child++;
			if (_arr[child] > _arr[parent])
			{
				std::swap(_arr[child], _arr[parent]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

		MyPriorityQueue()
			:_arr(nullptr)
			, _size(0)
			, _capacity(0) {
		}

		~MyPriorityQueue()
		{
			delete[] _arr;
			_arr = nullptr;
			_size = 0;
			_capacity = 0;
		}

		void push(const T & val)
		{
			expand();
			_arr[_size] = val;
			adjustUp(_size);
			_size++;
		}

		void pop()
		{
			std::swap(_arr[_size - 1], _arr[0]);
			_size--;
			adjustDown(0);
		}

		T& top()
		{
			assert(!empty());
			return _arr[0];
		}

		bool empty() const
		{
			return _size == 0;
		}

		size_t size() const
		{
			return _size;
		}

};


