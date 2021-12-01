#pragma once
#include <cassert>
#include"PriorityQueue.h"

template <class T> class LinkIterator;
template <class T> class LinkedList;

template <class T>
class Node
{
public:
	friend class LinkIterator<T>;
	friend class LinkedList<T>;
	Node() {}
	Node(int p, T d) :priority(p), data(d) {}
	//private:
	int priority;
	T data;
	Node* next;
	Node* prev;
};

template <class T>
class LinkIterator
{
public:
	friend class Node<T>;
	friend class LinkedList<T>;

	LinkIterator()
	{
		node = nullptr;
	}
	~LinkIterator() {}

	void operator=(Node<T>* linknode)
	{
		node = linknode;
	}

	T& operator*()
	{
		assert(node != nullptr);
		return node->data;
	}

	void operator++()
	{
		assert(node != nullptr);
		node = node->next;
	}
	void operator++(int)
	{
		assert(node != nullptr);
		node = node->next;
	}

	void operator--()
	{
		assert(node != nullptr);
		node = node->prev;
	}
	void operator--(int)
	{
		assert(node != nullptr);
		node = node->prev;
	}

	bool operator!=(Node<T>* linknode)
	{
		return (node != linknode);
	}
	bool operator==(Node<T>* linknode)
	{
		return (node == linknode);
	}
	bool isValid()
	{
		return (node != NULL);
	}

	Node<T>* node;
};

template <class T>
class LinkedList
{
public:
	friend class Node<T>;
	friend class LinkIterator<T>;

	LinkedList() :size(0), root(nullptr), lastNode(nullptr) {}
	~LinkedList()
	{
		while (root)
		{
			PopBack();
		}
	}

	Node<T>* Begin()
	{
		assert(root != nullptr);
		return root;
	}
	Node<T>* End()
	{
		return nullptr;
	}
	Node<T>* Last()
	{
		assert(lastNode != nullptr);
		return lastNode;
	}

	void InsertBefore(LinkIterator<T>& it, int newPriority, T newData)
	{
		assert(it.node != nullptr);

		Node<T>* linknode = new Node<T>;
		assert(linknode != nullptr);

		linknode->priority = newPriority;
		linknode->data = newData;
		linknode->next = it.node;
		linknode->prev = it.node->prev;

		if (linknode->prev != nullptr)
		{
			linknode->prev->next = linknode;
		}

		it.node->prev = linknode;

		if (it.node == root)
		{
			root = linknode;
		}

		size++;
	}

	void InsertAfter(LinkIterator<T>& it, int newPriority, T newData)
	{
		assert(it.node != nullptr);

		Node<T>* linknode = new Node<T>;
		assert(linknode != nullptr);

		linknode->priority = newPriority;
		linknode->data = newData;
		linknode->next = it.node->next;
		linknode->prev = it.node;

		if (linknode->next != nullptr)
		{
			linknode->next->prev = linknode;
		}

		it.node->next = linknode;

		if (it.node == lastNode)
		{
			lastNode = linknode;
		}

		size++;
	}

	void PushFront(int newPriority, T newData)
	{
		Node<T>* linknode = new Node<T>;
		assert(linknode != nullptr);

		linknode->priority = newPriority;
		linknode->data = newData;
		linknode->next = nullptr;
		linknode->prev = nullptr;

		if (root != nullptr)
		{
			linknode->next = root;
			root->prev = linknode;
			root = linknode;
		}
		else
		{
			root = linknode;
			lastNode = linknode;
		}

		size++;
	}
	void PopFront()
	{
		assert(root != nullptr);

		Node<T>* tmp = root;
		root = root->next;

		if (root != nullptr)
		{
			root->prev = nullptr;
		}
		else
		{
			lastNode = nullptr;
		}
		delete tmp;
		tmp = nullptr;

		size = (size == 0 ? size : size - 1);
	}
	void PushBack(int newPriority, T newData)
	{
		Node<T>* linknode = new Node<T>;
		assert(linknode != nullptr);

		linknode->priority = newPriority;
		linknode->data = newData;
		linknode->next = nullptr;
		linknode->prev = nullptr;

		if (lastNode != nullptr)
		{
			lastNode->next = linknode;
			linknode->prev = lastNode;
			lastNode = linknode;
		}
		else
		{
			root = linknode;
			lastNode = linknode;
		}

		size++;
	}
	void PopBack()
	{
		assert(root != nullptr);

		if (root->next == nullptr)
		{
			delete root;
			root = nullptr;
			lastNode = nullptr;
		}
		else
		{
			Node<T>* prevNode = lastNode->prev;
			prevNode->next = nullptr;
			delete lastNode;
			lastNode = prevNode;
			prevNode = nullptr;
		}

		size = (size == 0 ? size : size - 1);
	}
	int GetSize()
	{
		return size;
	}

private:
	int size;
	Node<T>* root;
	Node<T>* lastNode;
};