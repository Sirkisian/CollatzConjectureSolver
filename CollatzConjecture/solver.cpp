#include "solver.hpp"

template <class T>
bool Solver<T>::solve(const VecNumber<T> & number, std::array<VecNumber<T>, 3> & result, bool show)
{
	if(number.validNumber())
	{
		if(!(VecNumber<T>(2) > number)) //Number > 1
		{
			VecNumber<T> oddCount;
			VecNumber<T> evenCount;
			VecNumber<T> maximum;

			VecNumber<T> value = number;

			while(1) //Can be changed to a limit
			{
				if(value.isOne())
				{
					break;
				}
				else
				{
					if(value.isEven())
					{
						value = value / 2;

						evenCount++;
					}
					else
					{
						value = (value * 3) + 1;

						oddCount++;
					}

					if(value > maximum)
					{
						maximum = value;
					}

					if(show)
					{
						std::cout << value << " " << std::endl;
					}
				}
			}

			if(show)
			{
				std::cout << std::endl;
			}

			result[0] = oddCount;
			result[1] = evenCount;
			result[2] = maximum;

			return true;
		}
	}

	return false;
}

template class Solver<int>;
template class Solver<char>;
template class Solver<unsigned int>;
template class Solver<unsigned char>;