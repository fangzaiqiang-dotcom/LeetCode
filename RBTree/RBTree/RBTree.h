#pragma once
#include<iostream>
using namespace std;

enum Colour
{
	RED,
	BLACK
};

template<class T>
struct RBTreeNode
{
	typedef RBTreeNode<T>  Node;
	Node* _left;
	Node* _right;
	Node* _parent;
	T _data;
	Colour _col;
	
	RBTreeNode(const T& data)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_data(data)
	    ,_col(RED){}
 
};







template <class K>
struct SetKeyOfT
{
	const K& operator()(const K& key)
	{
		return key;
	}
};
template <class K, class T>
struct MapKeyOfT
{
	const K& operator ()(const pair< K, T>& kv)
	{
		return kv.first;
    }
};







template<class k,class T,class KeyOfT>
class RBTree
{
	typedef RBTreeNode<T> Node;



	void _Inorder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_Inorder(root->_left);
		cout << root->_data;
		if (root->_col == RED)
		{
			cout << "(R) ";
		}
		else
		{
			cout << "(B) ";
		}
		_Inorder(root->_right);
	}



	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* Gparent = parent->_parent;

		subR->_left = parent;
		parent->_right = subRL;

		subR->_parent = Gparent;
		if (Gparent == nullptr)
		{
			_root = subR;
		}
		else if (parent == Gparent->_left)
		{
			Gparent->_left = subR;
			subR->_parent = Gparent;
		}
		else
		{
			Gparent->_right = subR;
			subR->_parent = Gparent;
		}
		if(subRL)
		{

			parent->_right = subRL;
		}
		parent->_parent = subR;	 
	}


	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* Gparent = parent->_parent;

		subL->_right = parent;
		parent->_left = subLR;

		subL->_parent = Gparent;
		if (Gparent == nullptr)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else if (parent == Gparent->_right)
		{
			Gparent->_right = subL;
		}
		else
		{
			Gparent->_left = subL;
		}
		if (subLR)
		{
			subLR->_parent = parent;
			parent->_left = subLR;
		}
		parent->_parent = subL;
	}













public:	
	pair<iterator,bool> Insert(const T& data)
	{
		KeyOfT kot;
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return { iterator(_root), true };
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			parent = cur;
			if (kot(data) < kot(cur->_data))
			{
				cur = cur->_left;
			}
		else if(kot(data) > kot(cur->_data))
			{
				cur = cur->_right;
			}
		else
		   {
			return { iterator(cur), false };
	    	}
		}
		cur = new Node(data);
		cur->_parent = parent;
		if (kot(data) < kot(parent->_data))
		{
			parent->_left = cur;
		}
		else 
		{
			parent->_right = cur;
		}

		while (parent&& parent->_col == RED)
		{
			Node* Gparent = parent->_parent;
			if ( parent==Gparent->_left)
			{
					Node* uncle = Gparent->_right;
					if (uncle && uncle->_col == RED)
					{
						parent->_col = BLACK;
						Gparent->_col = RED;
						uncle->_col = BLACK;
						cur = Gparent;
						parent = cur->_parent;
					}
					else
					{
						if (cur == parent->_left)
						{
							RotateR(Gparent);
							Gparent->_col = RED;
							parent->_col = BLACK;
							break;
						}
						else
						{
							RotateL(parent);
							RotateR(Gparent);
							cur->_col = BLACK;
							Gparent->_col = RED;
							break;
						}
					}		
			}
			else
			{	
					Node* uncle = Gparent->_left;
					if (uncle && uncle->_col == RED)
					{
						parent->_col = BLACK;
						Gparent->_col = RED;
						uncle->_col = BLACK;
						cur = Gparent;
						parent = cur->_parent;
					}
					else 
					{
						if (cur == parent->_right)
						{
							RotateL(Gparent);
							Gparent->_col = RED;
							parent->_col = BLACK;
							break;
						}
						else
						{
							RotateR(parent);
							RotateL(Gparent);
							cur->_col = BLACK;
							Gparent->_col = RED;
							break;
						}
					}				
			}
		}
		_root->_col = BLACK;
		return { iterator(cur), true };
	}






	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}
	
	iterator begin()
	{
		Node* cur = _root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		return iterator(cur);
	}

	iterator end()
	{
		return iterator(nullptr);
	}


	class iterator
	{
	public:
		Node* _node;


		iterator(Node* node)
			:_node(node) {}

			T& operator*()
		{
			return _node->_data;
		}


		iterator& operator++()
		{
			if (_node->_right)
			{
				Node* cur = _node->_right;
				while (cur->_left)
				{
					cur = cur->_left;
				}
				_node = cur;
			}
			else
			{
				Node* parent = _node->_parent;
				while (parent)
				{
					if (_node == parent->_left)
					{
						_node = parent;
						return *this;
					}
					_node = parent;
					parent = parent->_parent;
				}
				_node = nullptr;
			}
			return *this;
		}

		iterator& operator--()
		{
			if (_node->_left)
			{
				Node* cur = _node->_left;
				while (cur->_right)
				{
					cur = cur->_right;
				}
				_node = cur;
			}
			else
			{
				Node* parent = _node->_parent;
				while (parent)
				{
					if (_node == parent->_right)
					{
						_node = parent;
						return *this;
					}
					_node = parent;
					parent = parent->_parent;
				}
				_node = nullptr;
			}
			return *this;
		}

		bool  operator!=(const iterator& it)const
		{
			return _node != it._node;
		}

		bool  operator==(const iterator& it)const
		{
			return _node == it._node;
		}

		T* operator->()
		{
			return &_node->_data;
		}
	};
private:
	Node* _root = nullptr;
};