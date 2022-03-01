// Given a chain <A1, A2, ... , An> of n matrices, where for i = 1, 2, ..., n,
// matrix A(i) has dimension p(i - 1) * p(i), fully parenthesize the product
// A1*A2*...An in a way that minimizes the number of scalar multiplications.

#include <vector>
#include <iostream>
#include <utility>
#include <limits>

using matrix_t = std::vector<std::vector<int>>;

matrix_t get_matrix (int rows, int columns) {
	matrix_t m(rows);
	for (auto& v : m) v.resize(columns);
	
	return m;
}

std::pair<matrix_t, matrix_t> matrix_chain_order (std::vector<int>& p) {
	const int n {static_cast<int>(p.size()) - 1};
	matrix_t m {get_matrix(n, n)};
	matrix_t s {get_matrix(n, n)};
	
	for (int i = 0; i < n; ++i)
		m[i][i] = 0;

	for (int l = 2; l <= n; ++l) {					// l is the chain length
		for (int i = 0; i < n - l + 1; ++i) {
			int j = i + l - 1;
			m[i][j] = std::numeric_limits<int>::max();
			for (int k = i; k < j; ++k) {
				int q = m[i][k] + m[k+1][j] + p[i] * p[k+1] * p[j+1];
				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
	return {m, s};
}

void print_optimal_parens (matrix_t& s, int i, int j) {
	if (i == j)
		std::cout << "A" << i + 1;
	else {
		std::cout << '(';
		print_optimal_parens (s, i, s[i][j]);
		print_optimal_parens (s, s[i][j] + 1, j);
		std::cout << ')';
	}
}

int main()
{
	std::vector<int> p {30, 35, 15, 5, 10, 20, 25};
	auto result {matrix_chain_order(p)};
	print_optimal_parens (result.second, 0, p.size() - 2);
	std::cout << '\n';

	return 0;
}
