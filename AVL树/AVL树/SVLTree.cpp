#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
struct Node
{
	int val;
	Node* left;
	Node* right;
	int height;
	Node(int v) :val(v), left(nullptr), right(nullptr), height(1){}
};

class AVLTree
{
private:
	Node* root;

	int getHeight(Node* node)
	{
		return node ? node->height : 0;
	}

	int getBalance(Node* node)
	{
		return node ? getHeight(node->right) - getHeight(node->left) : 0;
	}

	Node* rightRotate(Node* P)
	{
		Node* PL = P->left;
		Node* PLR = PL->right;

		PL->right = P;
		P->left = PLR;
		
		PL->height = getHeight(PL->left) > getHeight(PL->right) ? getHeight(PL->left) + 1 : getHeight(PL->right) + 1;
		P->height = getHeight(P->left) > getHeight(P->right) ? getHeight(P->left) + 1 : getHeight(P->right) + 1;
		return PL;
	}

	Node* leftRotate(Node* P)
	{
		Node* PR = P->right;
		Node* PRL = PR->left;

		PR->left = P;
		P->right = PRL;

		PR->height = getHeight(PR->left) > getHeight(PR->right) ? getHeight(PR->left) + 1 : getHeight(PR->right) + 1;
		P->height = getHeight(P->left) > getHeight(P->right) ? getHeight(P->left) + 1 : getHeight(P->right) + 1;
		return PR;
	}

	Node* insert(Node* node, int val)
	{
		if (!node)return new Node(val);
		if (val < node->val)
			node->left=insert(node->left, val);
		else if (val > node->val)
			node->right=insert(node->right, val);
		else
			return node;

		node->height=1+ max(getHeight(node->left), getHeight(node->right));
		int balance = getBalance(node);
		//右旋
		if (balance < -1 && val < node->left->val)
		{
			return rightRotate(node);
		}

		//左旋
		if (balance > 1 && val > node->right->val)
		{
			return leftRotate(node);
		}
		//左右旋
		if (balance < -1 && val > node->left->val)
		{
			node->left=leftRotate(node->left);
			return rightRotate(node);
		}
		//右左旋
		if (balance > 1 && val < node->right->val)
		{
			node->right=rightRotate(node->right);
			return leftRotate(node);
		}

		return node;
	}
	void inOrder(Node* root)
	{
		if (!root)return;
		inOrder(root->left);
		cout << root->val << " " << endl;
		inOrder(root->right);
	}
public:
	AVLTree() : root(nullptr) {}
	void insert(int val)
	{
		root = insert(root, val);
	}
	void print() 
	{
		inOrder(root);
	}
};