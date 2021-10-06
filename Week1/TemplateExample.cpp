#include <iostream>
using namespace std;

template <class T>
T min_func(T lVal, T rVal)
{
	if (lVal > rVal)
	{
		return rVal;
	}

	return lVal;
}

template <class T>
T max_func(T lVal, T rVal)
{
	if (lVal < rVal)
	{
		return rVal;
	}

	return lVal;
}

template <class T>
class TemplateClass
{
public:
	TemplateClass(T val)
	{
		m_val = val;
	}

	bool operator<(TemplateClass& rVal)
	{
		return m_val < rVal.GetVal();
	}
	bool operator>(TemplateClass& rVal)
	{
		return m_val > rVal.GetVal();
	}
	T GetVal()
	{
		return m_val;
	}
private:
	T m_val;
};

/*
// Main function
int main()
{
	cout << "Template Example" << endl << endl;
	cout << "Min = " << min_func(56.1, 43.6) << endl;
	cout << "Max = " << max_func('c', 'd') << endl;

	// Create 2 "TemplateClass" objects and compare them.
	cout << "Max (objects) = " << max_func(TemplateClass<int>(7), TemplateClass<int>(4)).GetVal();

	return 0;
}
*/