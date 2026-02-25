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

	std::ifstream mtdata("data.csv");
	if (!mtdata.is_open())
	{
		throw(NotopenException());
	}
	if (mtdata.is_open())
	{
		std::string line;
		std::getline(mtdata, line);
		while (std::getline(mtdata, line))
		{
			pose = line.find(',');
			if (pose != std::string::npos)
			{
				std::string date = line.substr(0, pose);
				std::string ratestr = line.substr(pose + 1);
				rate = atof(ratestr.c_str());
				_data[date] = rate;
			}
		}
	}
	mtdata.close();
}

void BitcoinExchange::calculate(const std::string &filename)
{
    std::ifstream myinput(filename);
    if(!myinput.is_open())
    {
        throw(NotopenException());
    }
    if(myinput.is_open())
    {
        std::string line;
        std::getline(myinput,line);
        while (std::getline(myinput,line))
        {
            size_t pos=line.find('|');
            if(pos!=std::string::npos)
            {
                std::string date =line.substr(0,pos);
                std::string ratestr=line.substr(pos+1);
                if(date)

            }
        }
        
    }

}