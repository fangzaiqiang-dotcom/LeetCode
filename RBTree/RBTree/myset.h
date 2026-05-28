#pragma once
#include"RBTree.h"
template<class K>
class set
{
	typedef SetKeyOfT<K> KeyOfT;

public:
	typedef typename
		RBTree<K, K, KeyOfT>::iterator iterator;

	iterator begin()
	{
		return _t.begin();
	}

	iterator end()
	{
		return _t.end();
	}

	bool insert(const K& k )
	{
		return _t.Insert(k);
	}
private:
	RBTree<K, K, KeyOfT> _t;
};