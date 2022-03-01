// Given an array of integers A. Find n-th smallest integer.
// If it is exists, then return its index, else return -1.

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int partition (std::vector<int>& a, int p, int r) {
	int i {p - 1};
	int k {i};
	int x {a[r]};
	for (int j = p; j < r; ++j) {
		if (a[j] < x) {
			std::swap(a[j], a[++i]);
			if (++k > i)
				std::swap(a[k], a[j]);
		}
		else if (a[j] == x) {
			std::swap(a[++k], a[j]);
		}
	}
	std::swap(a[++k], a[r]);
	return i + (k - i) / 2 + 1;
}

int getRandomNumber (int min, int max) {
	static constexpr double fraction {1.0 / (RAND_MAX + 1.0)};
	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

int randomized_partition (std::vector<int>& a, int p, int r) {
	int i {getRandomNumber(p, r)};
	std::swap(a[i], a[r]);
	return partition(a, p, r);
}

int nth_smallest_integer (std::vector<int> a, int n) {	
	int p {0};
	int r {static_cast<int>(a.size()) - 1};
	if (n - 1 < p || n - 1 > r)
		return -1;
	
	int q {randomized_partition(a, p, r)};
	while (n - 1 != q) {
		if (n - 1 < q)
			q = randomized_partition(a, p, r = q - 1);
		else
			q = randomized_partition(a, p = q + 1, r);
	}
	return a[q];
}

void test_nth_smallest_integer (const std::vector<int>& a, int n, int exp_res) {
	int result{};
	std::cout << "Returned expected result: "
		<< (((result = nth_smallest_integer(a, n)) == exp_res) ?
				"true" : "false") << '\n';
	std::cout << "expected: " << exp_res << ", returned: " << result << '\n';
}

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	std::rand();

	test_nth_smallest_integer({}, 0, -1);
	test_nth_smallest_integer({1,2}, 4, -1);
	test_nth_smallest_integer({3,5,1,2,4,6,7,9}, 5, 5);
	test_nth_smallest_integer({3,5,1,2,4,6,7,9}, 1, 1);
	test_nth_smallest_integer({3,5,1,2,4,6,7,9}, 8, 9);
	test_nth_smallest_integer({2}, 1, 2);
	test_nth_smallest_integer({1,3,4,4,5,4,4,6,4}, 4, 4);
	test_nth_smallest_integer({1,3,4,4,5,4,4,6,4}, 7, 4);

	return 0;
}
