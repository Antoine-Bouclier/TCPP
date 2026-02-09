#include <iostream>
#include <vector>

int	main(void)
{
	std::vector<int>	v;

	for (int i = 1; i <= 10; ++i)
		v.push_back(i);
	for (std::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend();)
	{
		if (*it % 2 == 0)
			it = std::vector<int>::reverse_iterator(v.erase((++it).base()));
		else
			++it;
	}
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
}