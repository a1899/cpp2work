#include "vector.h"
#include <iostream>
#include <string>

class SampleClass
{
	int m_x{};
	double m_y{};
	char m_z{};
public:
	SampleClass() = default;
	SampleClass(int x, double y, char z) : m_x{ x }, m_y{ y }, m_z{ z } {}
	friend std::ostream& operator<< (std::ostream& out, const SampleClass& s)
	{
		out << s.m_x << " " << s.m_y << " " << s.m_z;
		return out;
	}
};

template<typename T>
void print(const Vector<T>& v)
{
	for (const auto& x : v)
		std::cout << x << " ";
	std::cout << '\n';
}

int main()
{
	Vector<SampleClass> v1;
	v1.push_back(SampleClass{2, 4.0, 'c'});
	v1.emplace_back(3, 8.3, 'e');
	print(v1);

	Vector<SampleClass> v2{ v1 };
	Vector<SampleClass> v3{ std::move(v2) };
	v3.pop_back();
	v3.pop_back();
	print(v3);

	Vector<std::string> v4;
	v4.shrink_to_fit();
	v4 = { "pqr", "stu", "vw", "xyz" };
	print(v4);

	return 0;
}