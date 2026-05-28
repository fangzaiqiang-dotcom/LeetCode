#pragma once
#include"RBTree.h"

template<class K,class T>
class map
{
	typedef MapKeyOfT<K,T> KeyOfT;

public:
	typedef typename
		RBTree<K, pair<K,T>, KeyOfT>::iterator iterator;

	iterator begin()
	{
		return _t.begin();
	}

	iterator end()
	{
		return _t.end();
	}

	pair<iterator, bool> insert(const pair<K,T>& kv)
	{
		return _t.Insert(kv);
	}

	T& operator[](const K& key)
	{
		pair<iterator, bool> ret = _t.Insert({ key, T() });
		return ret.first->second;
	}


private:
	RBTree<K, pair<K,T>, KeyOfT> _t;
};