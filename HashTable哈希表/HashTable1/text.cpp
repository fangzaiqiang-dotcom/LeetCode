#include"unordered_map.h"
#include<string>
#include<iostream>


int main()
{
	unordered_map<std::string, int> map;

	map.insert(std::make_pair("apple", 10));
	map["banana"] = 20;
	map["orange"] = 30;

	auto it = map.find("apple");
	if (it != map.end())
	{
		std::cout << "find it->" <<it->first <<" " << it->second << std::endl;
	}

	for (auto& kv : map)
	{
		std::cout << kv.first << " : " << kv.second << std::endl;
	}

	// 删除
	map.erase("banana");

	for (auto& kv : map)
	{
		std::cout << kv.first << " : " << kv.second << std::endl;
	}
	return 0;
}