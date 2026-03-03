#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN &other)
{
	*this = other;
}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		this->_data = other._data;
	}
	return (*this);
}

void RPN::calculate(std::string input)
{
	int size = input.size();
	for (int i = 0; i < size; i++)
	{
		if (input[i] == ' ' || input[i] == '\t')
			continue;
		if (isdigit(input[i]))
		{
			int value = input[i] - '0';
			_data.push(value);
		}
		else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
		{
			if (_data.size() < 2)
				throw std::runtime_error("Error");
			int b = _data.top();
			_data.pop();
			int a = _data.top();
			_data.pop();
			if (input[i] == '+')
			_data.push(a + b);
			else if (input[i] == '-')
			_data.push(a - b);
			else if (input[i] == '*')
			_data.push(a * b);
			else if (input[i] == '/')
			{
				if (b == 0)
					throw std::runtime_error("Error");
				_data.push(a / b);
			}
		}
		else
		{
			throw std::runtime_error("Error");
		}
	}
	if (_data.size() != 1)
		throw std::runtime_error("Error");

	std::cout << _data.top() << std::endl;
}

RPN::~RPN()
{
}