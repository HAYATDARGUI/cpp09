#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		this->_data = other._data;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}
const char *BitcoinExchange::NotopenException::what() const throw()
{
	return ("Error: could not open file");
}
void BitcoinExchange::readData(const std::string &filename)
{
	size_t	pose;
	float	rate;

	std::ifstream mydata(filename);
	if (!mydata.is_open())
	{
		throw(NotopenException());
	}
	if (mydata.is_open())
	{
		std::string line;
		std::getline(mydata, line);
		while (std::getline(mydata, line))
		{
			pose = line.find(',');
			if (pose == std::string::npos)
			{
				std::cerr << "Error: bad input => " << line << std::endl;
				continue ;
			}
			std::string date = line.substr(0, pose);
			std::string ratestr = line.substr(pose + 1);
			rate = atof(ratestr.c_str());
			_data[date] = rate;
		}
	}
	mydata.close();
}

bool BitcoinExchange::isvalidDate(const std::string &date)
{
	int		year;
	int		month;
	int		day;
	bool	yearkabissa;

	if (date.length() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	year = atoi(date.substr(0, 4).c_str());
	month = atoi(date.substr(5, 2).c_str());
	day = atoi(date.substr(8, 2).c_str());
	if (month < 1 || month > 12)
		return (false);
	if (day < 1 || day > 31)
		return (false);
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return (false);
	if (month == 2)
	{
		yearkabissa = (year % 4 == 0);
		if (yearkabissa == true && day > 29)
			return (false);
		if (yearkabissa == false && day > 28)
			return (false);
	}
	return (true);
}

void BitcoinExchange::calculate(const std::string &filename)
{
	size_t	pos;
	float	rate;

	std::ifstream myinput(filename);
	if (!myinput.is_open())
	{
		throw(NotopenException());
	}
	if (myinput.is_open())
	{
		std::string line;
		if(!std::getline(myinput, line))
			return;
		if (line.find("date") == std::string::npos || line.find("|")== std::string::npos || line.find("value") == std::string::npos  )
   	 		std::cerr << "Error: invalid header format." << std::endl;
		while (std::getline(myinput, line))
		{
			pos = line.find('|');
			if (pos == std::string::npos)
			{
				std::cerr << "Error: bad input => " << line << std::endl;
				continue ;
			}
			std::string date = line.substr(0, pos);
			date.erase(std::remove(date.begin(), date.end(), ' '), date.end());
			if (!isvalidDate(date))
			{
				std::cerr << "Error: bad input => " << date << std::endl;
				continue ;
			}
			std::string ratestr = line.substr(pos + 1);
			rate = atof(ratestr.c_str());
			if (rate < 0)
			{
				std::cerr << "Error: not a positive number." << std::endl;
				continue ;
			}
			if (rate > 1000)
			{
				std::cerr << "Error: too large a number." << std::endl;
				continue ;
			}
			std::map<std::string, float>::iterator it = _data.lower_bound(date);
			if (it != _data.begin() && (it == _data.end() || it->first != date))
			{
				--it;
			}
			if (it == _data.begin() && it->first > date)
			{
				std::cerr << "Error: bad input => " << date << std::endl;
				continue ;
			}
			std::cout << date << " => " << rate << " = " << (rate * it->second) << std::endl;
		}
	}
}
