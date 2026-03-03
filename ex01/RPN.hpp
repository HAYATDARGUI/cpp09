#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
#include <stack>
class RPN
{
  private:
	std::stack<int> _data;

  public:
	RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	void calculate(std::string input);
	~RPN();
};

#endif