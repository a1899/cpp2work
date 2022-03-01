// Find the nonempty, contiguous subarray of a given 
// integer array whose values have the largest sum.

#include <iostream>
#include <vector>
#include <limits>

using array_t = std::vector<int>;

struct Max_t {
	int low;
	int high;
	int sum;
};

Max_t max_subarray(array_t& data) {
	Max_t max{-1, -1, std::numeric_limits<int>::min()};
	for(int j = 0; j < data.size(); ++j) {
		int sum{0};
		for(int i = j; i < data.size(); ++i) {
			sum += data[i];
			if(max.sum < sum)
				max = {j, i, sum};	
		}
	}
	return max;
}

Max_t cross_max_subarray(array_t& data, int p, int q, int r) {
	int leftSum{std::numeric_limits<int>::min()};
	int maxLeft{-1};
	int sum{0};
	for(int i = q; i >= p; --i) {
		sum += data[i];
		if(leftSum < sum) {
			leftSum = sum;
			maxLeft = i;
		}
	}
	int rightSum{std::numeric_limits<int>::min()};
	int maxRight{-1};
	sum = 0;
	for(int i = q + 1; i <= r; ++i) {
		sum += data[i];
		if(rightSum < sum) {
			rightSum = sum;
			maxRight = i;
		}
	}
	return {maxLeft, maxRight, leftSum + rightSum};
}

Max_t rec_max_subarray(array_t& data, int p, int r) {
	if(p == r)
		return {p, r, data[p]};

	int q{(r - p)/2 + p};
	Max_t left{rec_max_subarray(data, p, q)};
	Max_t right{rec_max_subarray(data, q + 1, r)};
	Max_t cross{cross_max_subarray(data, p, q, r)};

	if(left.sum >= right.sum && left.sum >= cross.sum)
		return left;
	else if(right.sum >= cross.sum)
		return right;
	else
		return cross;
}

Max_t linear_max_subarray(array_t& data) {
	Max_t max{0, 0, std::numeric_limits<int>::min()};
	int sum{0};
	for(int i = 0; i < data.size(); ++i) {
		if(sum < 0) {
			sum = 0;
			max.low = i;
		}
		sum += data[i];
		if(max.sum < sum) {
			max.sum = sum;
			max.high = i;
		}
	}
	return max;
}

int main()
{
	array_t data{13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
	Max_t max{linear_max_subarray(data)};
	std::cout << "low: " << max.low << " high: " << max.high
		<< " sum: " << max.sum << '\n';
}
