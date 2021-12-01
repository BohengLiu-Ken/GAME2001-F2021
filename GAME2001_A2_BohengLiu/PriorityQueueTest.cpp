#include<iostream>
#include"PriorityQueue.h"
using namespace std;

class less_cmp
{
public:
	inline bool operator()(int lPriority, int rPriority)
	{
		return lPriority < rPriority;
	}
};

class greater_cmp
{
public:
	inline bool operator()(int lPriority, int rPriority)
	{
		return !(lPriority < rPriority);
	}

};

int main()
{
	cout << "Priority Queue Test!" << endl;

	const int SIZE = 4;
	PriorityQueue<int, less_cmp>que(SIZE);

	que.Push(3, 2);
	que.Push(1, 12);
	que.Push(2, 22);
	que.Push(3, 25);

	cout << "Priority queue content (Size - " << que.GetSize() << ") : " << endl;

	while (que.IsEmpty() == false)
	{
		cout << "  Data: " << que.Front();
		cout << endl;

		que.Pop();
	}

	cout << endl;

	if (que.IsEmpty() == true)
	{
		cout << "The container is empty." << endl;
	}
	else
	{
		cout << "The container is NOT empty." << endl;
	}

	return 0;
}