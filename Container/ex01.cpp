#include <iostream>
#include <vector>

int	main(void)
{
	std::vector<int>			vector;
	std::vector<int>::iterator	it;

	vector.push_back(5);
	vector.push_back(10);
	vector.push_back(15);
	vector.push_back(20);
	for (it = vector.begin(); it != vector.end(); ++it)
		std::cout << *it << std::endl;
	return (0);
}