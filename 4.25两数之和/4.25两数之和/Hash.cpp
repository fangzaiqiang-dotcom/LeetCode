/*#include <iostream>
#include <vector>
#include <list>
#include <iterator>
using namespace std;

class HashTable {
private:
    vector<list<pair<int, string>>> table;  // 哈希表，数组存链表
    int capacity;  // 哈希表的大小
public:
    // 构造函数，初始化哈希表大小
    HashTable(int size) {
        capacity = size;
        table.resize(capacity);
    }

    // 哈希函数
    int hashFunction(int key) {
        return key % capacity;  // 简单的取模哈希
    }

    // 插入操作
    void insert(int key, string value) {
        int index = hashFunction(key);  // 计算哈希值
        bool found = false;

        // 检查该桶中是否已经有该键
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;  // 更新值
                found = true;
                break;
            }
        }

        if (!found) {
            table[index].push_back(make_pair(key, value));  // 插入新键值对
        }
    }

    // 查找操作
    string search(int key) {
        int index = hashFunction(key);  // 计算哈希值

        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;  // 返回对应的值
            }
        }
        return "Not Found";  // 如果没有找到该键
    }

    // 删除操作
    void remove(int key) {
        int index = hashFunction(key);  // 计算哈希值
        auto& bucket = table[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);  // 删除键值对
                return;
            }
        }
    }

    // 打印哈希表（用于调试）
    void printTable() {
        for (int i = 0; i < capacity; ++i) {
            cout << "Bucket " << i << ": ";
            for (auto& pair : table[i]) {
                cout << "[" << pair.first << ": " << pair.second << "] ";
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable ht(5);  // 创建一个大小为5的哈希表

    ht.insert(1, "Alice");
    ht.insert(2, "Bob");
    ht.insert(3, "Charlie");
    ht.insert(6, "David");

    cout << "Search for key 2: " << ht.search(2) << endl;
    cout << "Search for key 4: " << ht.search(4) << endl;

    ht.remove(2);  // 删除键2
    cout << "After removal, search for key 2: " << ht.search(2) << endl;

    // 打印哈希表
    ht.printTable();

    return 0;
}*/