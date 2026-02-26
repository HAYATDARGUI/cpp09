#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <exception>

class BitcoinExchange {
private:
    std::map<std::string, float> _data;

    bool isvalidDate(const std::string& date) ;
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    class NotopenException:public std::exception
    {
        virtual const char* what() const throw();
    };
    void readData(const std::string& filename); 
    void calculate(const std::string& filename); 
};

#endif