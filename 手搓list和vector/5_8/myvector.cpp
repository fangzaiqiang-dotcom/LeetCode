using namespace std;
template<class T>
class Myvector
{
public:
	Myvector()
		:_size(0)
		, _capacity(4)
	{
		_data = new T[_capacity];
	}
	Myvector(size_t n)
	{
		_data = new T[n];
		_size = n;
		_capacity = n;
	}
	Myvector(size_t n, const T& data)
	{
		_data = new T[n];
		for (size_t i = 0;i < n;i++)
		{
			_data[i] = data;
		}
		_size = n;
		_capacity = n;
	}
	Myvector(const Myvector& vv)
	{
		_data = new T[vv._capacity];
		for (size_t i = 0;i < vv._size;i++)
		{
			_data[i] = vv._data[i];
		}
		_capacity = vv._capacity;
		_size = vv._size;

	}

	~Myvector()
	{
		delete[] _data;
		_data = nullptr;
	}

	Myvector& operator=(const Myvector& vv)
	{
		if (this == &vv)return *this;
		delete[] _data;
		_data = new T[vv._capacity];
		for (size_t i = 0;i < vv._size;i++)
		{
			_data[i] = vv._data[i];
		}
		_size = vv._size;
		_capacity = vv._capacity;
		return *this;
	}

	size_t size()const
	{
		return _size;
	}
	size_t capacity()const
	{
		return _capacity;
	}

	bool empty()const
	{
		return _size == 0;
	}

	void reserve(size_t n)
	{
		if (n <= _capacity)return;
			T* data = new T[n];
			for (size_t i = 0;i < _size;i++)
			{
				data[i] = _data[i];
			}
			delete[]_data;
			_data = data;
			_capacity = n;
	}

	void resize(size_t n)
	{
		if (n <= _size)
		{
			_size = n;
		}
		else
		{
			reserve(n);
			for (size_t i = _size; i < n; ++i)
			{
				_data[i] = T();
			}
			_size = n;
		}
	}
	
	T& operator[](size_t n)
	{
		return _data[n];
	}

	const T&  operator[](size_t n)const
	{
		return _data[n];
	}

	T& front()
	{
		return _data[0];
	}

	T& back()
	{
		return _data[_size-1];
	}

	void push_back(const T& data)
	{
		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : _capacity * 2);
		}
		_data[_size++] = data;
	}

	void pop_back()
	{
		if (_size > 0)
			_size--;
	}

	void clear()
	{
		_size = 0;
	}

	void swap(Myvector& vv)
	{
		swap(_data, vv._data);
		swap(_size, vv._size);
		swap(_capacity, vv._capacity);
	}

	typedef T* iterator;
	iterator  begin()
	{
		return _data;
	}
	iterator  end()
	{
		return _data + _size;
	}
	typedef const T* const_iterator;

	const_iterator  cbegin()const
	{
		return _data;
	}
	const_iterator  cend()const
	{
		return _data + _size ;
	}


private:
	T* _data=nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
};