#include "list.h"
#include <iostream>
#include <string>
#include <utility>

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
void print(const List<T>& l)
{
	std::cout << "size: " << l.size() << " empty(): " << l.empty() << '\n';
	for (const auto& x : l)
		std::cout << x << ' ';
	std::cout << '\n';
}

int main()
{
	List<SampleClass> list;
	list.push_back(SampleClass{ 1, 3.0, 'c' });
	list.emplace(list.begin(), 4, 6.7, 'g');
	print(list);

	list.erase(list.begin());
	list.clear();
	print(list);

	List<std::string> l;
	std::string s{ "-string-" };
	l.push_front(s);
	l.insert(l.end(), "-another string-");
	print(l);

	auto ll{ std::move(l) };
	List<std::string> copy;
	copy = ll;
	print(ll);

	return 0;
}