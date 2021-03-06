#pragma once
#include <cassert>

#define QUICKSORT_CUTOFF 4

template<class T>
class UnorderedArray
{
public:
	// Constructor
	UnorderedArray(int size, int growBy = 1) :
		m_array(nullptr), m_maxSize(0), m_growSize(0), m_numElements(0)
	{
		if (size)	// Is this a legal size for an array?
		{
			m_maxSize = size;
			m_array = new T[m_maxSize];		// Dynamically allocating an array to m_maxSize
			memset(m_array, 0, sizeof(T) * m_maxSize);	// Explicitly set 0 to all elements in the array

			m_growSize = ((growBy > 0) ? growBy : 0);
		}
	}
	// Destructor
	~UnorderedArray()
	{
		if (m_array != nullptr)
		{
			delete[] m_array;
			m_array = nullptr;
		}
	}
	// Insertion
	// Fast insertion for UnorderedArray -- Big-O is O(1)
	void push(T val)
	{
		assert(m_array != nullptr); // Debugging purposes

		if (m_numElements >= m_maxSize)	// Check if the array has to expand to accommodate the new data.
		{
			Expand();
		}

		// My array has space for a new value. Let's add it!
		m_array[m_numElements] = val;
		m_numElements++;
	}
	// Deletion (2 ways)
	// Remove the last item inserted into the array
	void pop()
	{
		if (m_numElements > 0)
		{
			m_numElements--;	// Reduce the total number of elements by 1. Ignoring the last element.
		}
	}
	// Remove an item given an index
	// (Almost) Brute-force execution -- Big-O = O(N)
	void remove(int index)
	{
		assert(m_array != nullptr);

		if (index >= m_numElements)
		{
			// I am trying to remove something outside of the bounds of the array
			return;	// <-- Maybe could do some form of exception handling
		}

		for (int i = index; i < m_numElements; i++)
		{
			// Start at the index we want to remove.
			// Shift everything after index back by one.
			if (i + 1 < m_numElements)	// Confines the loop into the array
			{
				m_array[i] = m_array[i + 1];
			}
		}
		m_numElements--;
	}
	// Searching
	// Linear Search
	int search(T val)
	{
		assert(m_array != nullptr);

		// Brute-force Search
		for (int i = 0; i < m_numElements; i++)
		{
			if (m_array[i] == val)
			{
				return i;	// Return the index of where the item is located in the array
			}
		}

		return -1;
	}
	// ---------------- SORTING ALGORITHMS --------------------------------
	// Bubble Sort -- Big O = O(N^2)
	void BubbleSort()
	{
		assert(m_array != nullptr);

		T temp;

		for (int k = m_numElements - 1; k > 0; k--)	// Start at the end of the array and move backwards
		{
			for (int i = 0; i < k; i++)	 // Compare elements until k is reached
			{
				// Compare 2 adjacent elements
				if (m_array[i] > m_array[i + 1])
				{
					// Swap the elements
					temp = m_array[i];
					m_array[i] = m_array[i + 1];
					m_array[i + 1] = temp;
				}
			}
		}
	}
	// Selection Sort -- Big O = O(N^2)
	void SelectionSort()
	{
		assert(m_array != nullptr);

		T temp;	// Swapping
		int min = 0;	// Hold the index of the current smallest value

		// The lowest position to swap elements into
		for (int k = 0; k < m_numElements; k++)
		{
			min = k;	// Set the value at index k as a "default" minimum value

			// Iterate through the array to find smallest value, if there is one.
			for (int i = k + 1; i < m_numElements; i++)
			{
				// Compare the value at the current index vs the current "min" index
				if (m_array[i] < m_array[min])
				{
					// Store the index to the smallest element
					min = i;
				}
			}

			// Swap the lowest element with the lowest available index
			if (m_array[k] > m_array[min])
			{
				// Swap
				temp = m_array[k];
				m_array[k] = m_array[min];
				m_array[min] = temp;
			}
		}
	}
	// Insertion Sort -- Big O = O(N^2)
	void InsertionSort()
	{
		assert(m_array != nullptr);

		T temp;
		int i = 0;

		for (int k = 1; k < m_numElements; k++) // Iterate through all elements to be sorted.
		{
			temp = m_array[k];
			i = k;

			// Shifting of elements if necessary. Create a space for an elements
			// to be inserted in the correct location.
			while (i > 0 && m_array[i - 1] >= temp)
			{
				// Push elements to the right
				m_array[i] = m_array[i - 1];
				i--;
			}

			// Place the item in temp into the correct location
			m_array[i] = temp;
		}
	}
	// Merge Srot -- Big O = O(N logN)
	void MergeSort()
	{
		assert(m_array != nullptr);

		T* tempArray = new T[m_numElements];
		assert(tempArray != nullptr);

		MergeSort(tempArray, 0, m_numElements - 1);
		delete[] tempArray;
	}

	// ------------ ADVANCED SORTING ALGORITHMS ----------------
	void Shellsort()
	{
		assert(m_array != nullptr);
		T temp;
		int i = 0, k = 0;

		// Define our gap balue using the Knuth method
		int seq = 1;

		while (seq <= m_numElements / 3)
		{
			// Knuth: h = h * 3 + 1
			seq = seq * 3 + 1;
		}

		// Start sorting!
		while (seq > 0)
		{
			for (k = seq; k < m_numElements; k++)
			{
				temp = m_array[k];	// Stores m_array[k] in temp
				i = k;

				// Loop to the end of the array
				// Maintain our gap of "seq"
				// Compare the 2 values together
				while (i > seq - 1 && m_array[i - seq] >= temp)
				{
					// Swap the 2 compared values
					m_array[i] = m_array[i - seq];
					i -= seq;
				}

				m_array[i] = temp;
			}

			// "Inverse" of Knuth Formula to get the next lowest gap value
			seq = (seq - 1) / 3;
		}
	}
	void SwapElements(int index1, int index2)
	{
		assert(index1 >= 0 && index1 < m_numElements);
		assert(index2 >= 0 && index2 < m_numElements);
		assert(m_array != nullptr);

		// Swap elements
		T temp = m_array[index1];
		m_array[index1] = m_array[index2];
		m_array[index2] = temp;
	}
	void QuickSort()
	{
		// Call a private QuickSort function
		QuickSort(0, m_numElements - 1);
	}

	//int Partition(T pivot)
	//{
	//	return Partition(0, m_numElements - 1, pivot);
	//}

	//int Partition(int lIndex, int rIndex, T pivot)
	//{
	//	int currentLeft = lIndex;
	//	int currentRight = rIndex;

	//	while (1)
	//	{
	//		// Traverse from left to right
	//		while (currentLeft < rIndex && m_array[currentLeft] < pivot)
	//		{
	//			// m_array[currentLeft] is smaller than the pivot
	//			// Increment by one
	//			currentLeft++;
	//		}

	//		// Traverse from right to left
	//		while (currentRight > lIndex && m_array[currentRight] > pivot)
	//		{
	//			// m_array[currentRight] is greater than the pivot
	//			// Decrement by one
	//			currentRight--;
	//		}

	//		// Check to see if currentLeft and currentRight have crossed.
	//		if (currentLeft >= currentRight)
	//		{
	//			// Done partitioning
	//			break;
	//		}

	//		// Swap Elements
	//		SwapElements(currentLeft, currentRight);
	//	}

	//	// Return the pivot index
	//	return currentLeft;
	//}

	// Overloaded [] operator
	T& operator[](int index)
	{
		assert(m_array != nullptr && index < m_numElements);
		return m_array[index];
	}
	// Clear
	void clear()
	{
		m_numElements = 0;	 // Ignore (or forgets) all current items in the array
	}
	// Gets and Sets
	int GetSize()
	{
		return m_numElements;
	}
	int GetMaxSize()
	{
		return m_maxSize;
	}
	int GetGrowSize()
	{
		return m_growSize;
	}
	int SetGrowSize(int val)
	{
		assert(val >= 0);
		m_growSize = val;
	}
private:
	// Private functions
		// Quick sort using Median of Three
	void QuickSort(int lVal, int rVal)
	{
		// Check whether I have enough items to do a quicksort
		// If not, dp an insertionsort instead.
		if ((rVal - lVal + 1) < QUICKSORT_CUTOFF)
		{
			// Not enough items for a quicksort
			// Do InsertionSort
			InsertionSort(lVal, rVal);
			return;
		}

		// Median of 3. Select far left, center and far right
		// Center = Middle of something
		// Centre = Building

		int center = (lVal + rVal) / 2;

		// Order the left, center and right values
		if (m_array[lVal] > m_array[center])
		{
			SwapElements(lVal, center);
		}
		if (m_array[lVal] > m_array[rVal])
		{
			SwapElements(lVal, rVal);
		}
		if (m_array[center] > m_array[rVal])
		{
			SwapElements(center, rVal);
		}

		int pivotIndex = Partition(lVal, rVal, center);

		QuickSort(lVal, pivotIndex - 1);	// Quicksort the left half
		QuickSort(pivotIndex, rVal);		// Quicksort the right half

	}

	int Partition(int lIndex, int rIndex, int pivot)
	{
		while (1)
		{
			while (m_array[++lIndex] < m_array[pivot]);
			while (m_array[--rIndex] > m_array[pivot]);

			if (lIndex >= rIndex)
			{
				// Done partitioning
				break;
			}

			SwapElements(lIndex, rIndex);
		}

		return lIndex;
	}

	void InsertionSort(int lVal, int rVal)
	{
		assert(m_array != nullptr);

		T temp;
		int i = 0;

		for (int k = lVal + 1; k <= rVal; k++) // Iterate through all elements to be sorted.
		{
			temp = m_array[k];
			i = k;

			// Shifting of elements if necessary. Create a space for an elements
			// to be inserted in the correct location.
			while (i > lVal && m_array[i - 1] >= temp)
			{
				// Push elements to the right
				m_array[i] = m_array[i - 1];
				i--;
			}

			// Place the item in temp into the correct location
			m_array[i] = temp;
		}
	}

	// Recursive Merge Sort
	void MergeSort(T* tempArray, int lowerBound, int upperBound)
	{
		// Base case
		if (lowerBound == upperBound)
		{
			return;
		}

		// Determine the middle of the array
		int mid = (lowerBound + upperBound) >> 1;

		MergeSort(tempArray, lowerBound, mid);	// Mergesort the lower half of the array
		MergeSort(tempArray, mid + 1, upperBound); // Mergesort the upper half of the array

		// Merge
		Merge(tempArray, lowerBound, mid + 1, upperBound);
	}
	void Merge(T* tempArray, int low, int mid, int upper)
	{
		// Lowerbound, Mid+1, Upperbound
		int tempLow = low, tempMid = mid - 1;
		int index = 0;

		while (low <= tempMid && mid <= upper)
		{
			// Which of the 2 values is smaller then move it into the temp array
			if (m_array[low] < m_array[mid])
			{
				tempArray[index++] = m_array[low++];	// Left half lower value is the lowest
			}
			else
			{
				tempArray[index++] = m_array[mid++];	// Right half lower value is the lowest.
			}
		}

		while (low <= tempMid) // Clean up lower half
		{
			tempArray[index++] = m_array[low++];
		}
		while (mid <= upper) // Clean up upper half
		{
			tempArray[index++] = m_array[mid++];
		}

		// Place the stored tempArray into the main array in the correct locations
		for (int i = 0; i < upper - tempLow + 1; i++)
		{
			m_array[tempLow + i] = tempArray[i];
		}
	}
	// Expansion
	bool Expand()
	{
		if (m_growSize <= 0)
		{
			// LEAVE!
			return false;
		}

		// Create the new array
		T* temp = new T[m_maxSize + m_growSize];
		assert(temp != nullptr);

		// Copy the contents of the original array into the new array
		memcpy(temp, m_array, sizeof(T) * m_maxSize);

		// Delete the old array
		delete[] m_array;

		// Clean up variable assignments
		m_array = temp;
		temp = nullptr;

		m_maxSize += m_growSize;

		return true;
	}
private:
	// Private Variables
	T* m_array;			// Pointer to the beginning of the array

	int m_maxSize;		// Maximum size of the array
	int m_growSize;		// Amount the array can grow through expansion
	int m_numElements;	// Number of items currently in my array
};