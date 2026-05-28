#pragma once
#include <iostream>
#include <assert.h>
#include <string.h>
#include <utility>
using namespace std;
namespace string
{
	class mystring
	{
	public:
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
			size_t len = strlen(str);
			_str = new char[len + 1];
			memcpy(_str, str, len+1);
			_size = len;
			_capacity = len;
		}
			mystring(const mystring& str)
			{
				_str = new char[str._capacity + 1];
				memcpy(_str, str._str, str._size+1);
				_size =str._size;
				_capacity = str._capacity;
            }

			~mystring()
			{
				delete[]_str;
				_size = 0;
				_capacity = 0;
			}

			mystring& operator=(mystring str)
			{
				swap(str);
				return *this;
			}

			void swap(mystring& str)
			{
				std::swap(_str, str._str);
				std::swap(_size, str._size);
				std::swap(_capacity, str._capacity);
			}

			void reserve(size_t n)
			{
				if (n <= _capacity)
					return;
				char* str = new char[n + 1];
				memcpy(str, _str, _size + 1);
				delete[]_str;
				_str = str;
				_capacity = n;
			}
			void push_back(char ch)
			{
				if (_size == _capacity)
				{
					reserve(_capacity == 0 ? 4 : 2 * _capacity);
				}
				_str[_size] = ch;
				_str[_size + 1] = '\0';
				_size++;
			}

			char& operator[](size_t pos)
			{
				assert(pos <_size);
				return _str[pos];
			}

			const char& operator[](size_t pos)const
			{
				assert(pos < _size);
				return _str[pos];
			}
			size_t size()const
			{
				return _size;
			}

			bool empty()const
			{
				return _size == 0;
			}

			void append(const char* s)
			{
				assert(s != nullptr);
				size_t len=strlen(s);
				reserve(_size+len);
				for (size_t i = _size;i < _size + len;i++)
				{
					_str[i] = *s;
					s++;
				}
				_str[_size + len] = '\0';
				_size+=len;
		    }


			void erase(size_t pos=0)
			{
				assert(pos < _size);
				_str[pos] = '\0';
				_size = pos;
			}

			// 插入单个字符（面试必考版）
			void insert(size_t pos, char ch)
			{
				assert(pos <= _size);
				if (_size == _capacity)
				{
					reserve(_capacity == 0 ? 4 : _capacity * 2);
				}
				size_t end = _size;
				while (end >= pos)
				{
					_str[end + 1] = _str[end];
					end--;
				}
				_str[pos] = ch;
				_size++;
				_str[_size] = '\0';
			}


	public:
		const static size_t npos;
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
	const size_t mystring::npos = -1;
}