#include<iostream>
#include <windows.h> 
using namespace std;
template<class T>
struct TreeNode
{
	T val;
	TreeNode* left;
	TreeNode* right;
	TreeNode()
		:val(),left(nullptr),right(nullptr){}
	TreeNode(T v)
		:val(v),left(nullptr),right(nullptr){}
};
template<class T>
class BST
{
private:
	TreeNode<T>*  root;
	TreeNode<T>* insert(TreeNode<T>* node, T v)
	{
		if (!node) return new TreeNode(v);
		if (v < node->val)
			node->left = insert(node->left, v);
		else if (v > node->val)
			node->right = insert(node->right, v);
		return node;
	}

	bool search(TreeNode<T>* node, T v)
	{
		if (!node)return false;
		if (node->val == v) return true;
		if (v < node->val)
			return search(node->left, v);
		else
			return search(node->right, v);
	}

	TreeNode<T>* getMax(TreeNode<T>* node)
	{
		while (node->right)
			node = node->right;
		return node;
	}

	TreeNode<T>* remove(TreeNode<T>* node, T val)
	{
		if (!node)return nullptr;
		if (val < node->val)
			node->left = remove(node->left, val);
		else if (val > node->val)
			node->right = remove(node->right, val);
		else
		{
			if (!node->left || !node->right)
			{
				TreeNode<T>* tmp = node->left ? node->left : node->right;
				delete node;
				return tmp;
			}
			TreeNode<T>* maxLeft = getMax(node->left);
			node->val = maxLeft->val;
			node->left = remove(node->left, maxLeft->val);
		}
		return node;
	}
	void inOrder(TreeNode<T>* node)
	{
		if (!node)return;
		inOrder(node->left);
		cout << node->val << " ";
		inOrder(node->right);
	}

	void destory(TreeNode<T>* node)
	{
		if (!node)return;
		destory(node->left);
		destory(node->right);
		delete(node);
	}

public:
	BST():root(nullptr){}
	~BST() { destory(root); }
	void _insert(T val) { root = insert(root, val); }
	bool find(T val) { return search(root, val); }
	void del(T val) { root = remove(root, val); }
	void show()
	{
		inOrder(root);
		cout << endl;
	}

};


int main()
{
	// 设置控制台输出编码为 UTF-8
	SetConsoleOutputCP(CP_UTF8);
	// （可选）设置控制台输入编码为 UTF-8
	SetConsoleCP(CP_UTF8);


	BST<int> tree;

	// 插入数据
	tree._insert(5);
	tree._insert(3);
	tree._insert(7);
	tree._insert(2);
	tree._insert(4);
	tree._insert(6);
	tree._insert(8);

	cout << "中序遍历(升序)：";
	tree.show();

	// 查找
	cout << "查找4：" << (tree.find(4) ? "存在" : "不存在") << endl;
	cout << "查找9：" << (tree.find(9) ? "存在" : "不存在") << endl;

	// 删除叶子节点
	tree.del(2);
	cout << "删除叶子2后：";
	tree.show();

	// 删除单孩子节点
	tree.del(3);
	cout << "删除单孩子3后：";
	tree.show();

	// 删除双孩子根节点
	tree.del(5);
	cout << "删除根节点5后：";
	tree.show();

	return 0;
}