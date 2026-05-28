#include<iostream>
template<class T>
struct ListNode
{
	T data;
	ListNode* prve;
	ListNode* next;

	ListNode(const T& val=T())
		:data(val)
		,prve(nullptr)
		,next(nullptr){ }
};

template<class T>
class Mylist
{
private:
	ListNode<T>* head;
	size_t _size;

public:
	Mylist():_size(0)
	{
		head = new ListNode<T>();
		head->next = head;
		head->prve = head;
	}

	~Mylist()
	{
		clear();
		delete head;
		head = nullptr;
    }

	Mylist(const Mylist<T>& other)
		:Mylist()
	{
		for (ListNode<T>* cur = other.head->next;cur != other.head;cur = cur->next)
		{
			push_back(cur->data);
		}
	}

	Mylist<T>& operator=(const Mylist<T>& other)
	{
		if (this != &other)
		{
			Mylist<T> temp(other);
			std::swap(head, temp.head);
			std::swap(_size, temp._size);
		}
		return *this;
	}

	bool empty()const
	{
		return _size == 0;
	}

	size_t size()const
	{
		return _size;
	}

	void clear()
	{
		while (!empty())
			pop_front();
	}

	T& front()
	{
		return head->next->data;
    }

	T& back()
	{
		return head->prve->data;
	}

	void push_front(const T& val)
	{
		ListNode<T>* newnode = new ListNode<T>(val);
		ListNode<T>* first = head->next;

		head->next = newnode;
		newnode->prve = head;
		newnode->next = first;
		first->prve = newnode;
		++_size;
	}

	void pop_front()
	{
		ListNode<T>* firstnode = head->next;
		head->next = firstnode->next;
		firstnode->next->prve = head;
		delete firstnode;
		_size--;
	}



	void push_back(const T& val)
	{
		ListNode<T>* newnode = new ListNode<T>(val);
		ListNode<T>* prvnode = head->prve;

		newnode->next = head;
		prvnode->next = newnode;
		newnode->prve = prvnode;
		head->prve = newnode;
		_size++;
	}



	void pop_back()
	{
		if (empty())return;
		ListNode<T>* end = head->prve;
		ListNode<T>* prvenode = end->prve;
		prvenode->next = head;
		head->prve = prvenode;
		delete end;
		_size--;
	}

	ListNode<T>* insert(ListNode<T>* pos,const T& val)
	{
		if (pos == nullptr)return nullptr;
		ListNode<T>* newnode = new ListNode<T>(val);
		ListNode<T>* prenode = pos->prve;
		
		newnode->prve = prenode;
		newnode->next = pos;
		prenode->next = newnode;
		pos->prve = newnode;

		++_size;
		return newnode;
	}

	void erase(ListNode<T>* pos)
	{
		if (pos == nullptr || pos == head)return;
		ListNode<T>* prvnode = pos->prve;
		ListNode<T>* nextnode = pos->next;
		prvnode->next = nextnode;
		nextnode->prve = prvnode;
		delete pos;
		_size--;
	}

	ListNode<T>* begin()
	{
		return head->next;
	}

	ListNode<T>* end()
	{
		return head->prve;
	}
};