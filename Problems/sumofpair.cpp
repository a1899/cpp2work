// Given an array A and number K. Find a pair of numbers (a, b)
// from a given array, such that a + b = K.

#include <vector>
#include <iostream>
#include <utility>
#include <unordered_map>

using pair_t = std::pair<int, int>;

pair_t sum_of_pair (const std::vector<int>& a, int k) {
	std::unordered_map<int, int> temp;
	for (int i = 0; i < a.size(); ++i) {
		if (temp.contains(k - a[i]))
			return {temp[k-a[i]], i};
		else
			temp[a[i]] = i;
	}
	return {-1, -1};
}

bool test_sum_of_pair (const std::vector<int>& a, int k, pair_t exp_res) {
	std::cout << "Testing sum_of_pair() for K = " << k << "... ";
	pair_t result {sum_of_pair(a, k)};
	if (result == exp_res) {
		std::cout << "ok.\n";
		return true;
	}
	else {
		std::cout << "\nExpected to get (" << exp_res.first
			<< ", " << exp_res.second << "), but got ("
			<< result.first << ", " << result.second
			<< ").\n";
		return false;
	}
}

int main()
{
	return !(test_sum_of_pair({1,3,5,6,7}, 9, {1,3}) &&
		test_sum_of_pair({1,3,5,6,7}, 20, {-1,-1}) &&
		test_sum_of_pair({}, 10, {-1,-1}) &&
		test_sum_of_pair({-4,5,3,-2,9,1}, 1, {0,1}));
}
