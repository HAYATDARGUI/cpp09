#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}
PmergeMe::PmergeMe(const PmergeMe &other)
{
	*this = other;
}
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
	}
	return (*this);
}
PmergeMe::~PmergeMe()
{
}

void PmergeMe::parseInput(int ac, char **av)
{
	int	val;

	for (int i = 1; i < ac; i++)
	{
		std::string s = av[i];
		if (s.empty() || s.find_first_not_of("0123456789") != std::string::npos)
			throw std::runtime_error("Error");
		val = std::atoi(av[i]);
		if (val < 0)
			throw std::runtime_error("Error");
		_vec.push_back(val);
		_deq.push_back(val);
	}
}

void PmergeMe::fordJohnsonVector(std::vector<int> &c)
{
	int		straggler;
	bool	hasStraggler;

	if (c.size() < 2)
		return ;
	straggler = -1;
	hasStraggler = false;
	if (c.size() % 2 != 0)
	{
		straggler = c.back();
		c.pop_back();
		hasStraggler = true;
	}
	std::vector<int> mainChain, pending;
	for (size_t i = 0; i < c.size(); i += 2)
	{
		if (c[i] < c[i + 1])
			std::swap(c[i], c[i + 1]);
		mainChain.push_back(c[i]);
		pending.push_back(c[i + 1]);
	}
	fordJohnsonVector(mainChain);
	for (size_t i = 0; i < pending.size(); i++)
	{
		std::vector<int>::iterator it = std::lower_bound(mainChain.begin(),
				mainChain.end(), pending[i]);
		mainChain.insert(it, pending[i]);
	}
	if (hasStraggler)
	{
		std::vector<int>::iterator it = std::lower_bound(mainChain.begin(),
				mainChain.end(), straggler);
		mainChain.insert(it, straggler);
	}
	c = mainChain;
}

void PmergeMe::fordJohnsonDeque(std::deque<int> &c)
{
	if (c.size() < 2)
		return ;

	int straggler = -1;
	bool hasStraggler = false;
	if (c.size() % 2 != 0)
	{
		straggler = c.back();
		c.pop_back();
		hasStraggler = true;
	}

	std::deque<int> mainChain, pending;
	for (size_t i = 0; i < c.size(); i += 2)
	{
		if (c[i] < c[i + 1])
			std::swap(c[i], c[i + 1]);
		mainChain.push_back(c[i]);
		pending.push_back(c[i + 1]);
	}

	fordJohnsonDeque(mainChain);

	for (size_t i = 0; i < pending.size(); i++)
	{
		std::deque<int>::iterator it = std::lower_bound(mainChain.begin(),
				mainChain.end(), pending[i]);
		mainChain.insert(it, pending[i]);
	}

	if (hasStraggler)
	{
		std::deque<int>::iterator it = std::lower_bound(mainChain.begin(),
				mainChain.end(), straggler);
		mainChain.insert(it, straggler);
	}
	c = mainChain;
}

void PmergeMe::sortVector() {
    clock_t start = clock();
    fordJohnsonVector(_vec);
    clock_t end = clock();
    _vecTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

void PmergeMe::sortDeque() {
    clock_t start = clock();
    fordJohnsonDeque(_deq);
    clock_t end = clock();
    _deqTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
}


void PmergeMe::printBefore() const {
    std::cout << "Before: ";
    for (size_t i = 0; i < _vec.size(); i++) {
        std::cout << _vec[i] << (i == _vec.size() - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

void PmergeMe::printAfter() const {
    std::cout << "After:  ";
    for (size_t i = 0; i < _vec.size(); i++) {
        std::cout << _vec[i] << (i == _vec.size() - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

double PmergeMe::getVecTime() const {
    return _vecTime;
}

double PmergeMe::getDeqTime() const {
    return _deqTime;
}

size_t PmergeMe::getSize() const {
    return _vec.size();
}