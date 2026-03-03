#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    PmergeMe sorter;

    try
    {
        sorter.parseInput(ac, av);

        sorter.printBefore();

        sorter.sortVector();

        sorter.sortDeque();

        sorter.printAfter();

        std::cout << "Time to process a range of " << sorter.getSize() 
                  << " elements with std::vector : " << std::fixed 
                  << std::setprecision(5) << sorter.getVecTime() << " us" << std::endl;

        std::cout << "Time to process a range of " << sorter.getSize() 
                  << " elements with std::deque  : " << std::fixed 
                  << std::setprecision(5) << sorter.getDeqTime() << " us" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}