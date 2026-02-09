#include <iostream>
#include <vector>
#include <list>

/* void test_vector(void)
{
	std::vector<int>			v = {1, 2, 3, 4, 5};
	std::vector<int>::iterator	it;

	it = v.begin();
	v.insert(it + 2, 42);
	for (it = v.begin(); it != v.end(); ++it)
		std::cout << *it << std::endl;
} */

void test_vector(void)
{
	std::vector<int>			v = {1, 2, 3, 4, 5};
	std::vector<int>::iterator	it;

	it = v.begin();
	v.insert(it + 2, 42);
	for (it = v.begin(); it != v.end(); ++it)
		std::cout << *it << std::endl;
}

void test_list(void)
{
	std::list<int>	l = {1, 2, 3, 4, 5};
}

int	main(void)
{
	test_vector();
	return 0;
}