#include "vecnumber.hpp"

template <class T>
VecNumber<T>::VecNumber()
{
	ExceptionHandler::push_back<T>(this->value, 0);
}

template <class T>
VecNumber<T>::VecNumber(unsigned int numberValue)
{
	std::string stringValue = std::to_string(numberValue);

	*this = stringValue;
}

template <class T>
VecNumber<T>::VecNumber(const std::string & stringValue)
{
	*this = stringValue;
}

template <class T>
VecNumber<T>::~VecNumber()
{
}

template <class T>
bool VecNumber<T>::isOne() const
{
	if(this->value.size() == 1)
	{
		return this->value.front() == 1;
	}

	return false;
}

template <class T>
bool VecNumber<T>::isEven() const
{
	if(!this->value.empty())
	{
		//Is the last number even?
		return this->value.back() % 2 == 0;
	}

	return false;
}

template <class T>
VecNumber<T> VecNumber<T>::operator=(const std::string & stringValue)
{
	try
	{
		this->setValue(stringValue);
	}
	catch(const std::exception &)
	{
		this->value.clear();
	}

	return *this;
}

template <class T>
VecNumber<T> VecNumber<T>::operator++(int)
{
	VecNumber returnValue = *this;

	*this = *this + 1;

	return returnValue;
}

template <class T>
VecNumber<T> VecNumber<T>::operator/(unsigned int number)
{
	std::vector<T> result;

	bool empty = true;
	T tmp1 = 0, tmp2 = 0, rest = 0;

	for(typename std::vector<T>::const_iterator i = this->value.begin(), j = this->value.end(); i != j; i++)
	{
		tmp1 = *i + rest;
		tmp2 = tmp1 / number;
		rest = (tmp1 % number) * 10;

		if(empty)
		{
			empty = result.empty();
		}

		if(!(empty && tmp2 == 0))
		{
			ExceptionHandler::push_back<T>(result, tmp2);
		}
	}

	return VecNumber(result);
}

template <class T>
VecNumber<T> VecNumber<T>::operator*(unsigned int number)
{
	VecNumber vecNumber = number;

	return *this * vecNumber;
}

template <class T>
VecNumber<T> VecNumber<T>::operator*(const VecNumber & number)
{
	VecNumber up = *this; //Number with more digits
	VecNumber down = number; //Number with less digits

	VecNumber::prepare(up, down);

	std::vector<T> tmp;
	std::vector<std::vector<T>> result;

	for(typename std::vector<T>::reverse_iterator i = down.value.rbegin(), j = down.value.rend(); i != j; i++)
	{
		tmp = this->multiply(up.value, *i);

		ExceptionHandler::push_back<std::vector<T>>(result, tmp);
	}

	VecNumber resultVecNumber;

	size_t size = result.size();

	if(size > 0)
	{
		resultVecNumber = VecNumber(result.front());
	}

	if(size > 1)
	{
		for(size_t i = 1; i < size; i++)
		{
			//Append zeros to the end
			result[i].insert(result[i].end(), i, 0);

			resultVecNumber = resultVecNumber + VecNumber(result[i]);
		}
	}

	return resultVecNumber;
}

template <class T>
VecNumber<T> VecNumber<T>::operator+(unsigned int number)
{
	VecNumber vecNumber = number;

	return *this + vecNumber;
}

template <class T>
VecNumber<T> VecNumber<T>::operator+(const VecNumber & number)
{
	VecNumber up = *this; //Number with more digits
	VecNumber down = number; //Number with less digits

	VecNumber::prepare(up, down);

	bool addDown = true;
	T tmp = 0, inc = 0;

	for(typename std::vector<T>::reverse_iterator i = up.value.rbegin(), j = up.value.rend(), k = down.value.rbegin(), l = down.value.rend(); i != j; i++)
	{
		if(addDown)
		{
			addDown = k != l;
		}

		tmp = *i + inc;

		if(addDown)
		{
			tmp += *k;

			k++;
		}

		if(tmp > 9)
		{
			*i = tmp % 10;
			inc = 1;
		}
		else
		{
			*i = tmp;
			inc = 0;

			if(!addDown)
			{
				break;
			}
		}
	}

	if(inc == 1)
	{
		ExceptionHandler::insert<T>(up.value, inc, up.value.begin());
	}

	return up;
}

template <class T>
bool VecNumber<T>::operator>(unsigned int number) const
{
	VecNumber vecNumber = number;

	return *this > vecNumber;
}

template <class T>
bool VecNumber<T>::operator>(const VecNumber & number) const
{
	size_t sizeA = this->value.size();
	size_t sizeB = number.value.size();

	if(sizeA != sizeB)
	{
		return sizeA > sizeB;
	}
	else
	{
		for(typename std::vector<T>::const_iterator i = this->value.begin(), j = this->value.end(), k = number.value.begin(); i != j; i++, k++)
		{
			if(*i != *k)
			{
				return *i > *k;
			}
		}
	}

	return false;
}

template <class T>
VecNumber<T>::VecNumber(const std::vector<T> & vectorValue):
value(vectorValue)
{
}

template <class T>
void VecNumber<T>::setValue(const std::string & stringValue)
{
	std::string error{"Invalid syntax!"};

	//Is empty?
	if(stringValue.empty())
	{
		throw std::invalid_argument(error);
	}
	else
	{
		//Is digit?
		std::string::const_iterator position = std::find_if(stringValue.begin(), stringValue.end(), [](const char & c){ return !std::isdigit(c); });

		if(position != stringValue.end())
		{
			throw std::invalid_argument(error);
		}
		else
		{
			char c;

			if(!this->value.empty())
			{
				this->value.clear();
			}

			for(std::string::const_iterator i = stringValue.begin(), j = stringValue.end(); i != j; i++)
			{
				c = *i;

				ExceptionHandler::push_back<T>(this->value, atoi(&c));
			}
		}
	}
}

template <class T>
void VecNumber<T>::prepare(VecNumber & up, VecNumber & down)
{
	if(down > up)
	{
		VecNumber tmp = up;
		up = down;
		down = tmp;
	}
}

template <class T>
std::vector<T> VecNumber<T>::multiply(const std::vector<T> & vectorValue, T number)
{
	std::vector<T> result;

	T tmp1 = 0, tmp2 = 0, rest = 0;

	for(typename std::vector<T>::const_reverse_iterator i = vectorValue.rbegin(), j = vectorValue.rend(); i != j; i++)
	{
		tmp1 = (*i * number) + rest;
		tmp2 = tmp1 % 10;
		rest = (tmp1 - tmp2) / 10;

		ExceptionHandler::insert<T>(result, tmp2, result.begin());
	}

	if(rest != 0)
	{
		ExceptionHandler::insert<T>(result, rest, result.begin());
	}

	return result;
}

template class VecNumber<int>;
template class VecNumber<char>;
template class VecNumber<unsigned int>;
template class VecNumber<unsigned char>;