
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>
#include <cstddef>

enum class State
{
	EXIST,
	EMPTY,
	DELETE
};


template<class K,class V>
struct HashData
{
	std::pair<K, V> kv;
	State state = State::EMPTY;
};



inline size_t GetNextPrime(size_t n)
{
	static const size_t primeList[] = {
		53u, 97u, 193u, 389u, 769u,
		1543u, 3079u, 6151u, 12289u, 24593u,
		49157u, 98317u, 196613u, 393241u, 786433u,
		1572869u, 3145739u, 6291469u, 12582917u, 25165843u,
		50331653u, 100663319u, 201326611u, 402653189u, 805306457u,
		1610612741u, 3221225473u, 4294967291u
	};
	const size_t* first = primeList;
	const size_t* last = primeList + sizeof(primeList) / sizeof(primeList[0]);
	const size_t* pos = std::lower_bound(first, last, n);
	return pos == last ? *(last - 1) : *pos;
}






template<class K,class V,class Hash = std::hash<K>>
class HashTable
{

public:
	HashTable() :_size(0)
	{
		_table.resize(GetNextPrime(53));
	}
	
	size_t HashIndex(const K& key) const
	{
		return std::hash<K>{}(key) % _table.size();
	}

	HashData<K, V>* Find(const K& key)
	{
		if (_table.empty())
		{
			return nullptr;
		}
		size_t index = HashIndex(key);
		size_t start = index;

		while (_table[index].state != State::EMPTY)
		{
			if (_table[index].state == State::EXIST && _table[index].kv.first == key)
			{
				return &_table[index];
			}
			index = (index + 1) % _table.size();
			if (index == start)
			{
				break;
			}
		}
		return nullptr;
	}

	

	bool Insert(const std::pair<K, V>& kv)
	{
		size_t index = HashIndex(kv.first);
		size_t firstDeleted = _table.size();

		// 一次循环，同时做：查重 + 记删除位 + 找空位
		while (_table[index].state != State::EMPTY)
		{
			// 1. 查重（发现重复直接返回）
			if (_table[index].state == State::EXIST &&
				_table[index].kv.first == kv.first)
			{
				return false;
			}

			// 2. 记录第一个删除位
			if (_table[index].state == State::DELETED &&
				firstDeleted == _table.size())
			{
				firstDeleted = index;
			}

			index = (index + 1) % _table.size();
		}

		// 3. 复用删除位 或 插入空位
		if (firstDeleted != _table.size())
			index = firstDeleted;

		_table[index].kv = kv;
		_table[index].state = State::EXIST;
		++_size;

		// 扩容...

		return true;
	}

	bool Erase(const& K key)
	{
		HashData<K, V>* node = Find(key);
		if (node == nullptr)
		{
			return false;
		}
		node->state = State::DELETE;
		--_size;
		return true;
	}

	V& FindValue(const K& key)
	{
		HashData<K, V>* node = Find(key);
		if (node)
		{
			return node->kv.second;
		}
		return nullptr;
	}
	size_t Size()
	{
		return _size;//_table.size;
	}

	bool Empty() const
	{
		return _size == 0;
	}

private:
	double LoadFactor()const
	{
		return _table.empty() ? 0.0 : static_cast<double>(_size) / _table.size();
	}
	size_t HashIndex(const K& key)const
	{
		return Hash{}(key) % _table.size;
	}

	void Rehash(size_t newCapacity)
	{
		std::vector<HashData<K, V>> oldtable;
		oldtable.swap(_table);
		_table.resize(newCapacity);
		_size = 0;
		for (auto& data : oldtable)
		{
			if (data.state == State::EXIST)
			{
				Insert(data.kv);
			}
		}
	}


private:
	std::vector<HashData<K, V>> _table;
	size_t _size;


};



#include <iostream>
#include <string>

int main()
{
	HashTable<int, int> ht;
	ht.Insert({ 1, 10 });
	ht.Insert({ 54, 20 }); // 如果容量是 53，这里会冲突

	auto p1 = ht.FindValue(1);
	auto p2 = ht.FindValue(54);

	ht.Erase(1);

	auto p3 = ht.FindValue(1);
	auto p4 = ht.FindValue(54);


	HashTable<std::string, int> hs;
	hs.Insert({ "apple", 100 });
	hs.Insert({ "banana", 200 });

	auto ps = hs.FindValue("banana");

	return 0;
}