#include "header.h"
#include <string>

int longestValidSubstring(const std::string& str)
{
	Stack<int> stk;
	stk.push(-1);

	int n{ static_cast<int>(str.size()) };
	int result{ 0 };

	for (int i{ 0 }; i < n; ++i)
	{
		if (str[i] == '(')
		{
			stk.push(i);
		}
		if (str[i] == ')')
		{
			stk.pop();
			if (!stk.empty())
			{
				if (result < i - stk.top())
					result = i - stk.top();
			}
			else
				stk.push(i);
		}
	}
	return result;
}

int maxHistArea(int* hist, int size)
{
	Stack<int> stk;
	int maxArea{ 0 };
	int areaWithTop{};
	int index{ 0 };

	for (; index < size; ++index)
	{
		while (!stk.empty() && hist[index] < hist[stk.top()])
		{
			areaWithTop = hist[stk.top()] * (index - stk.top());
			if (maxArea < areaWithTop)
				maxArea = areaWithTop;
			stk.pop();
		}
		stk.push(index);
	}

	while (!stk.empty())
	{
		areaWithTop = hist[stk.top()] * (index - stk.top());
		if (maxArea < areaWithTop)
			maxArea = areaWithTop;
		stk.pop();
	}

	return maxArea;
}