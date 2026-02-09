#include <iostream>
#include <vector>
#include <list>
#include <iterator>

void test_vector(void)
{
	std::vector<int>			v;
	std::vector<int>::iterator	it;

	for (int i = 1; i <= 5; i++)
		v.push_back(i);
	it = v.begin();
	v.insert(it + 2, 42);
	for (it = v.begin(); it != v.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
}

void test_list(void)
{
	std::list<int>				l;
	std::list<int>::iterator	it;

	for (int i = 1; i <= 5; i++)
		l.push_back(i);
	it = l.begin();
	std::advance(it, 2); // Ou ++it; ++it;
	l.insert(it, 42);
	for (it = l.begin(); it != l.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
}

int	main(void)
{
	test_vector();
	test_list();
	return 0;
}