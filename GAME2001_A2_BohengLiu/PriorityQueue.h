#pragma once
#include"LinkedList.h"

template<class T, class CMP>
class PriorityQueue
{
public:
	PriorityQueue(int queueSize)
	{
		assert(queueSize > 0);
		size = queueSize;
	}
	~PriorityQueue() {}

	void Push(int priority, T value)
	{
		assert(elements.GetSize() < size);

		if (elements.GetSize() == 0)
		{
			elements.PushBack(priority, value);
		}
		else
		{
			LinkIterator<T> it;
			it = elements.Begin();

			CMP cmp;	

			while (it.isValid())
			{
				if (cmp(priority, it.node->priority))
				{
					break;
				}
				it++;
			}

			if (it.isValid())
			{
				elements.InsertBefore(it, priority, value);
			}
			else
			{
				elements.PushBack(priority, value);
			}
		}
	}

	void Pop()
	{
		elements.PopFront();
	}

	T& Front()
	{
		LinkIterator<T> it;
		it = elements.Begin();

		return *it;
	}

	T& Back()
	{
		LinkIterator<T> it;
		it = elements.Last();

		return *it;
	}

	int GetSize()
	{
		return elements.GetSize();
	}
	int GetMaxSize()
	{
		return size;
	}
	bool IsEmpty()
	{
		return (elements.GetSize() == 0);
	}
	void Resize(int queueSize)
	{
		assert(queueSize > 0);
		size = queueSize;
	}

private:
	LinkedList<T> elements; 
	int size;				
};