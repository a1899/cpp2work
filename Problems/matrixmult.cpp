// The following procedure takes n*n matrices A and B 
// and multiplies them, returning their n*n product C.

#include <vector>
#include <iostream>

using matrix_t = std::vector<std::vector<int>>;

matrix_t get_square_matrix (int n) {
	matrix_t c(n);
	for (auto& v : c) v.resize(n, 0);
	return c;
}

matrix_t square_matrix_multiply (const matrix_t& a, const matrix_t& b) {
	const int n {static_cast<int>(a.size())};
	auto c {get_square_matrix(n)};

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return c;
}

matrix_t square_matrix_add (const matrix_t& a, const matrix_t& b) {
	const int n {static_cast<int>(a.size())};
	auto c {get_square_matrix(n)};

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return c;
}

void square_matrix_copy (const matrix_t& from, matrix_t& to, int row, int column) {
	int r {row + static_cast<int>(from.size())};
	int c {column + static_cast<int>(from.size())};

	for (int i = row; i < r; ++i) {
		for (int j = column; j < c; ++j) {
			to[i][j] = from[i - row][j - column];
		}
	}
}

matrix_t square_matrix_multiply_rec (const matrix_t& a, int ra, int ca,
	       				const matrix_t& b, int rb, int cb, int n) {
	auto c {get_square_matrix(n)};
	if (n == 1) {
		c[0][0] = a[ra][ca] * b[rb][cb];
		return c;
	}

	square_matrix_copy (square_matrix_add(
			square_matrix_multiply_rec(a, ra, ca, b, rb, cb, n/2), 
			square_matrix_multiply_rec(a, ra, ca + n/2, b, rb + n/2, cb, n/2)
			), c, 0, 0);
	square_matrix_copy (square_matrix_add(
			square_matrix_multiply_rec(a, ra, ca, b, rb, cb + n/2, n/2), 
			square_matrix_multiply_rec(a, ra, ca + n/2, b, rb + n/2, cb + n/2, n/2)
			), c, 0, n/2);
	square_matrix_copy (square_matrix_add(
			square_matrix_multiply_rec(a, ra + n/2, ca, b, rb, cb, n/2), 
			square_matrix_multiply_rec(a, ra + n/2, ca + n/2, b, rb + n/2, cb, n/2)
			), c, n/2, 0);
	square_matrix_copy (square_matrix_add(
			square_matrix_multiply_rec(a, ra + n/2, ca, b, rb, cb + n/2, n/2), 
			square_matrix_multiply_rec(a, ra + n/2, ca + n/2, b, rb + n/2, cb + n/2, n/2)
			), c, n/2, n/2);
	return c;
}

void print_square_matrix (const matrix_t& m) {
	const int n {static_cast<int>(m.size())};
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			std::cout << m[i][j] << ' ';
		std::cout << '\n';
	}
}

int main()
{
	constexpr int n{8};
	matrix_t a(n);
	for(auto& v : a) v.resize(n, 1);
	matrix_t b(n);
	for(auto& v : b) v.resize(n, 2);

	matrix_t c {square_matrix_multiply_rec(a, 0, 0, b, 0, 0, n)};
	print_square_matrix(c);

	return 0;
}
