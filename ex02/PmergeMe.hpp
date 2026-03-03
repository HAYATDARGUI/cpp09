#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <string>

class PmergeMe {
private:
    std::vector<int> _vec;
    std::deque<int> _deq;
	double _vecTime;
        double _deqTime;

public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void sortVector();
    void fordJohnsonVector(std::vector<int>& c);
    
    void sortDeque();
    void fordJohnsonDeque(std::deque<int>& c);

    void parseInput(int ac, char** av);
    void run(int ac, char** av);
	void printBefore() const ;
	void printAfter() const ;
	double getVecTime() const;
	double getDeqTime() const ;
	size_t getSize() const;
};

#endif