#pragma once
#include "Hashtable.h"
template <class K>
struct SetKeyOfT
{
	const K& operator()(const K& key)const
	{
		return key;
	}
};

template<class K, class T, class MapKeyOfT= SetKeyOfT<K>, class Hash = HashFunc<K>>
class unordered_set
{
public:
	typedef HashTable<K, K, SetKeyOfT<K>, Hash> HT;
	bool insert(const K& key)
	{
		return _ht.Insert(key);
	}
	bool find(const K& key)
	{
		return _ht.Find(key) != nullptr;
	}

	// 删除
	bool erase(const K& key)
	{
		return _ht.Erase(key);
	}

	typedef typename HT::iterator iterator;

	iterator begin()
	{
		return _ht.begin();
	}

	iterator end()
	{
		return _ht.end();
	}

private:
	HT _ht;

};
