#include <iostream>
#include <vector>
#include <functional>   // std::hash
#include <algorithm>    // 如果你用 lower_bound
#pragma once



inline size_t __stl_next_prime(size_t n)
{
	static const int __stl_num_primes = 28;
	static const size_t __stl_prime_list[__stl_num_primes] =
	{
		53,         97,         193,       389,       769,
		1543,       3079,       6151,      12289,     24593,
		49157,      98317,      196613,    393241,    786433,
		1572869,    3145739,    6291469,   12582917,  25165843,
		50331653,   100663319,  201326611, 402653189, 805306457,
		1610612741, 3221225473, 4294967291
	};

	for (int i = 0; i < __stl_num_primes; ++i)
	{
		if (__stl_prime_list[i] > n)
			return __stl_prime_list[i];
	}
	return __stl_prime_list[__stl_num_primes - 1];
}
template<class T>
struct HashNode
{
	HashNode<T>* _next;
	T _data;
	HashNode(const T& data)
		:_next(nullptr)
		,_data(data)
		{}
};

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)const
	{
		return (size_t)key;
	}
};

template<>
struct HashFunc<std::string>
{
	size_t operator()(const std::string& key)
	{
		size_t num = 0;
		for (auto ch : key)
		{
			num += ch;
			num *= 131;
		}
		return num;
	}
};

template<class K,class T,class KeyOfT,class Hash=HashFunc<K>>
class HashTable
{
	typedef HashNode<T> Node;
public:
	HashTable():_table(__stl_next_prime(1), nullptr),_size(0){}
	class iterator;

	iterator Find(const K& key)
	{
		size_t index = HashIndex(key);
		Node* cur = _table[index];
		KeyOfT kot;
		while (cur!=nullptr)
		{
			if (kot(cur->_data) == key)
			{
				return iterator(cur,this);
			}
			cur = cur->_next;
		}
		return end();
	}

	bool Insert(const T& data)
	{
		KeyOfT kot{};
	    if (Find(kot(data))!= end())
			return false;
		Node* newnode =new Node(data);
		size_t index = HashIndex(kot(data));
		newnode->_next = _table[index];
		_table[index] = newnode;
		_size++;
		return true;
	}

	bool Erase(const K& key)
	{
		if (Empty()) return false;
		size_t index = HashIndex(key);
		KeyOfT kot;
		Node* cur = _table[index];
		Node* pre = nullptr;
		while (cur)
		{
			if (kot(cur->_data) == key)
			{
				if (pre == nullptr)
				{
					_table[index] = cur->_next;
				}
				else
				{
					pre->_next = cur->_next;
				}
				delete(cur);
				--_size;
				return true;
			}
			pre = cur;
			cur = cur->_next;
		}
		return false;
	}

	
	void ReHash()
	{
		std::vector<Node*> newtable(__stl_next_prime(_table.size() + 1), nullptr);
		for (size_t i = 0;i < _table.size();i++)
		{
			Node* cur = _table[i];
			while(cur)
			{
				Node* next = cur->_next;
				KeyOfT kot;
				size_t index = Hash()(kot(cur->_data)) % newtable.size();
				cur->_next = newtable[index];
				newtable[index] = cur;
				cur = next;
			}
		}
		_table.swap(newtable);
	}



	size_t HashIndex(const K& key)
	{
		if (_table.empty())
			return 0;
		
		return  Hash()(key) % _table.size();
	}

	size_t Size()
	{
		return _table.size();
	}

	bool Empty()
	{
		return _size==0;
	}


	class iterator
	{
	public:
		Node* _node;
		HashTable* _pht;
		iterator(Node* node, HashTable* pht)
			:_node(node), _pht(pht) {}

		iterator& operator++()
		{
			if (_node->_next)
			{
				_node=_node->_next;
			}
			else
			{
				// 用 {} 显式初始化，消除警告
				KeyOfT kot;
				Hash hash_fun{};

				// 先转成 K，再哈希
				K key = kot(_node->_data);
				size_t index = hash_fun(key) % _pht->_table.size();

				index++;
				while (index < _pht->Size())
				{
					if (_pht->_table[index])
					{
						_node =_pht->_table[index];
						break;
					}
					index++;
				}
				if (index == _pht->Size())
					_node = nullptr;
			}
			return *this;
		}

		T& operator*()
		{
			return _node->_data;
		}

		T* operator->()
		{
			return &(_node->_data); // 加括号！关键！
		}

		const T* operator->() const
		{
			return &(_node->_data);
		}

		bool operator!=(const iterator& other)const
		{
			return _node != other._node;
		}
		bool operator==(const iterator& other)const
		{
			return _node == other._node;
		}


	};


	iterator begin()
	{
		for (size_t i = 0;i < _table.size();i++)
		{
			if (_table[i] != nullptr)
			{
				return iterator(_table[i], this);
			}
		}
		return end();
	}
	iterator end()
	{
		return iterator(nullptr, this);
	}



	private:
	std::vector<Node*> _table;
	size_t _size;
};