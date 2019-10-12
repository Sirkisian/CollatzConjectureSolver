#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include "exceptionhandler.hpp"

//Template class for storing string consisting of numbers "123456789" into array of numbers [1][2][3][4][5][6][7][8][9]
template <class T>
class VecNumber
{
	public:
		VecNumber();
		VecNumber(unsigned int numberValue);
		VecNumber(const std::string & stringValue);
		~VecNumber();

		inline bool validNumber() const
		{
			return !this->value.empty();
		}

		bool isOne() const;
		bool isEven() const;

		VecNumber operator=(const std::string & stringValue);
		VecNumber operator++(int); //postfix increment
		VecNumber operator/(unsigned int number);
		VecNumber operator*(unsigned int number);
		VecNumber operator*(const VecNumber & number);
		VecNumber operator+(unsigned int number);
		VecNumber operator+(const VecNumber & number);
		bool operator>(const VecNumber & number);

		friend std::ostream & operator<<(std::ostream & out, const VecNumber & number)
		{
			std::for_each(number.value.begin(), number.value.end(), [&out](const T & n){ out << static_cast<int>(n); });

			return out;
		}

	private:
		VecNumber(const std::vector<T> & vectorValue);

		void setValue(const std::string & stringValue);

		void prepare(VecNumber & up, VecNumber & down);

		std::vector<T> multiply(const std::vector<T> & vectorValue, T number);

		std::vector<T> value;
};