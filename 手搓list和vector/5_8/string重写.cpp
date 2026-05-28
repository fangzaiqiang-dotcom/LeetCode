#pragma once
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <string.h>
#include <utility>   // std::swap 定义在这里，必须加！
#include <cstddef>    // size_t 定义在这里，确保类型识别正确
using namespace std;
namespace string
{
	class mystring {
	public:
		static const size_t npos;
		mystring()
			:_str(new char[1])
			, _size(0)
			, _capacity(0)
		{
			_str[0] = '\0';
		}

		mystring(const char* str)
		{

			if (str == nullptr)
				str = "";
			_size=str ? strlen(str) : 0;
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str,str);
		}

		mystring(const mystring& s)
		{
			_str = new char[s._capacity + 1];
			memcpy(_str, s._str, s._size+1);
			_size = s._size;
			_capacity = s._capacity;
		}

		mystring& swap(mystring s) 
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
			return *this;
		}

		mystring& operator=(mystring s)
		{
			return swap(s);
		}
		~mystring()
		{
			delete[] _str;
			_size = 0;
			_capacity = 0;
		}

		typedef char* iterator;
		typedef const char*  const_iterator;

		iterator begin()
		{ 
			return _str;
		}
		
		const_iterator begin() const
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		const_iterator end()const
		{
			return _str + _size;
		}

		size_t size()const
		{
			return _size;
		}

		size_t capacity()const
		{
			return _capacity;
		}

		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				memcpy(tmp, _str, _size + 1);
			delete[] _str;
			_str = tmp;
			_capacity = n;
			}
		}
		void resize(size_t n, char ch='\0')
		{
			if (n < _size)
			{
				_size = n;
				_str[_size] = '\0';
			}
			else
			{
				reserve(n);
				for (size_t i = _size;i < n;i++)
				{
					_str[i] = ch;
				}
				_size = n;
				_str[_size] = '\0';
			}
		}

		char& operator[](size_t n)
		{
			assert(n <_size);
			return _str[n];
		}

		const char& operator[](size_t n)const
		{
			assert(n < _size);
			return _str[n];
		}
		const char* c_str() const
		{
			return _str;
		}

		void pushback(const char ch)
		{
			if (_size == _capacity)
			{
				reserve(_size == 0 ? 4 : 2 * _capacity);
			}
			_str[_size] = ch;
			_size++;
			_str[_size] = '\0';
        }

		void append(const char* s)
		{
			size_t len = strlen(s);
			if (len + _size > _capacity)
			{
				reserve(len + _size);
			}

			memcpy(_str + _size, s, len + 1);
			_size += len;
		}

		void insert(size_t pos,char ch)
		{
			assert(pos <= _size);
			if (_capacity == _size)
			{
				reserve(_size == 0 ? 4 : 2 * _capacity);
			}
			size_t end = _size + 1;
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				end--;
			}
			_str[pos] = ch;
			_size++;
		}

	

		void erase(size_t pos=0, size_t len = npos)
		{
			assert(pos <= _size);
			if (pos + len >= _size||len==npos)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				memcpy(_str + pos, _str + pos + len, _size - pos - len + 1);
				_size -= len;
			}
		}


		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}

		mystring& operator+=(char ch)
		{
			pushback(ch);
			return*this;
		}

		mystring& operator+=(const char* s)
		{
			append(s);
			return*this;
		}

		size_t find(char ch, size_t pos=0)
		{
			assert(pos <= _size);
			while (pos < _size)
			{
				if (_str[pos] == ch)
				{
					return pos;
				}
				pos++;
			}
			return npos;
		}

		mystring substr(size_t pos=0, size_t len=npos)const
		{
			assert(pos <=_size);
			if (pos + len > _size || len == npos)
			{
				len = _size - pos;
			}
				mystring sub;
				sub.reserve(len);
				memcpy(sub._str, _str+pos, len);
				sub._str[len] = '\0';
				return sub;
		}

		bool operator>(mystring&str)const
		{
			return strcmp(_str, str._str) > 0;
		}

		bool operator==(mystring& str)const
		{
			return strcmp(_str, str._str) == 0;
		}

		bool operator<=(mystring& str)const
		{
			return !(*this > str);
		}

		bool operator<(mystring& str)const
		{
			return strcmp(_str, str._str) < 0;
		}
		bool operator>=(mystring& str)const
		{
			return !(*this < str);
		}

		bool operator!=(mystring& str)const
		{
			return !(*this == str);
		}

		private:
			char* _str;
			size_t _size;
			size_t _capacity;
	};
	const size_t mystring::npos = -1;
}