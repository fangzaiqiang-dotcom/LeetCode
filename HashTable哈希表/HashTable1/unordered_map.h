#pragma once
#include <utility>
#include "Hashtable.h"


template <class K, class T>
struct MapKeyOfT
{
	const K& operator()(const std::pair<K, T>& kv)const
	{
		return kv.first;
	}
};


template<class K, class T,class Hash = HashFunc<K>>
class unordered_map
{
public:
	// 👇 两行 typedef 必须放最前面！
	typedef HashTable<K, std::pair<K, T>,MapKeyOfT<K, T>, Hash> HT;
	typedef typename HT::iterator iterator;


	bool insert(const std::pair<K, T>& kv)
	{
		return _ht.Insert(kv);
	}

    iterator find(const K& key)
	{
		return _ht.Find(key);
	}
	bool erase(const K& key)
	{
		return _ht.Erase(key);
	}
	iterator begin()
	{
		return _ht.begin();
	}
	iterator end()
	{
		return _ht.end();
	}

	T& operator[](const K& key)
	{
		iterator it = _ht.Find(key);
		if (it != end())
		{
			return it->second;
		}
		_ht.Insert(std::make_pair(key, T()));
		return find(key)->second;
	}

private:
	HT _ht;
};

