#include <iostream>
using namespace std;

// 树节点结构
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BST
{
private:
    TreeNode* root;

    // 递归插入
    TreeNode* insert(TreeNode* node, int val)
    {
        // 空位置创建新节点
        if (!node) return new TreeNode(val);
        // 小往左
        if (val < node->val)
            node->left = insert(node->left, val);
        // 大往右
        else if (val > node->val)
            node->right = insert(node->right, val);
        // 相等不插入（BST默认去重）
        return node;
    }

    // 递归查找
    bool search(TreeNode* node, int val)
    {
        if (!node) return false;
        if (node->val == val) return true;
        if (val < node->val)
            return search(node->left, val);
        else
            return search(node->right, val);
    }

    // 找左子树最大值（删除用）
    TreeNode* getMax(TreeNode* node)
    {
        while (node->right) node = node->right;
        return node;
    }

    // 递归删除
    TreeNode* remove(TreeNode* node, int val)
    {
        if (!node) return nullptr;

        // 先找到要删的节点
        if (val < node->val)
            node->left = remove(node->left, val);
        else if (val > node->val)
            node->right = remove(node->right, val);
        else
        {
            // 三种删除情况
            // 1. 叶子节点 / 只有一个子节点
            if (!node->left || !node->right)
            {
                TreeNode* tmp = node->left ? node->left : node->right;
                delete node;
                return tmp;
            }
            // 2. 左右都有子节点：左子树最大值替换
            TreeNode* maxLeft = getMax(node->left);
            node->val = maxLeft->val;
            // 删掉原最大值节点
            node->left = remove(node->left, maxLeft->val);
        }
        return node;
    }

    // 中序遍历 升序
    void inOrder(TreeNode* node)
    {
        if (!node) return;
        inOrder(node->left);
        cout << node->val << " ";
        inOrder(node->right);
    }

    // 销毁整棵树
    void destory(TreeNode* node)
    {
        if (!node) return;
        destory(node->left);
        destory(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destory(root); }

    // 对外接口
    void add(int val) { root = insert(root, val); }
    bool find(int val) { return search(root, val); }
    void del(int val) { root = remove(root, val); }
    void show()
    {
        inOrder(root);
        cout << endl;
    }
};

// 测试
int main()
{
    BST bst;
    bst.add(5);
    bst.add(3);
    bst.add(7);
    bst.add(2);
    bst.add(4);
    bst.show();
    cout << "Find 3:" << (bst.find(3) ? "yes" : "no") << endl;
    cout << "Find 4:" << (bst.find(4) ? "yes" : "no") << endl;
    bst.del(3);
    cout << "delete 3:" << endl;
    bst.show();
    return 0;
}