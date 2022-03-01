// Given a rod of length n inches and a table of prices p(i)
// for i = 1, 2, ...,  n, determine the maximum revenue r(n) 
// obtainable by cutting up the rod and selling the pieces.

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <utility>

using array_t = std::vector<int>;

int cut_rod(const array_t& p, int n) {
	if(n == 0)
		return 0;
	int q {std::numeric_limits<int>::min()};
	for(int i{1}; i <= n; ++i)
		q = std::max(q, p[i] + cut_rod(p, n - i));
	return q;
}

int memoized_cut_rod_aux(const array_t& p, int n, array_t& r) {
	if(r[n] >= 0)
		return r[n];
	if(n == 0)
		return r[n] = 0;

	int q {std::numeric_limits<int>::min()};
	for(int i{1}; i <= n; ++i)
		q = std::max(q, p[i] + memoized_cut_rod_aux(p, n - i, r));
	return r[n] = q;
}

int memoized_cut_rod(const array_t& p, int n) {
	array_t r(n + 1);
	for(auto& x : r)
		x = std::numeric_limits<int>::min();
	return memoized_cut_rod_aux(p, n, r);
}

int bottom_up_cut_rod(const array_t& p, int n) {
	array_t r(n + 1);
	r[0] = 0;
	for(int j{1}; j <= n; ++j) {
		int q {std::numeric_limits<int>::min()};
		for(int i{1}; i <= j; ++i)
			q = std::max(q, p[i] + r[j - i]);
		r[j] = q;	
	}
	return r[n];
}

std::pair<array_t, array_t> extended_bottom_up_cut_rod(const array_t& p, int n) {
	array_t r(n + 1);
	array_t s(n + 1);
	r[0] = 0;
	for(int j{1}; j <= n; ++j) {
		int q {std::numeric_limits<int>::min()};
		for(int i{1}; i <= j; ++i)
			if(q < p[i] + r[j - i]) {
				q = p[i] + r[j - i];
				s[j] = i;
			}
		r[j] = q;
	}
	return {r, s};
}

void print_cut_rod_solution(const array_t& p, int n) {
	auto result {extended_bottom_up_cut_rod(p, n)};
	while(n > 0) {
		std::cout << result.second[n] << ' ';
		n -= result.second[n];
	}
}

int main()
{
	array_t p{0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	print_cut_rod_solution(p, 10);
	std::cout << '\n';

	return 0;
}
