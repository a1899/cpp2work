#include "vector.h"
#include "vector.cpp"
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

template class Vector<SampleClass>;
template class Vector<std::string>;