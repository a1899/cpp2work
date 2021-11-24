#include "header.h"
#include <iostream>
#include <string>

int main()
{
	std::string par{ "((()())(()())((()()))" };
	std::cout << longestValidSubstring(par) << '\n';
	int arr[]{ 4,5,7,8,4,5,2,6,7,8,9,6,6,7 };
	std::cout << maxHistArea(arr, sizeof(arr) / sizeof(int));

	return 0;
}
