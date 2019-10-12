#include "stringmanipulator.hpp"
#include "solver.hpp"

#define DTYPE int
//#define DTYPE char
//#define DTYPE unsigned int
//#define DTYPE unsigned char

int main()
{
	VecNumber<DTYPE> number;
	std::string input;

	std::cout << "Collatz Conjecture 'Solver'" << std::endl;

	std::cout << "(Use key [Enter] for exit)" << std::endl << std::endl;
	std::cout << "Number: ";

	while(std::getline(std::cin, input) && !input.empty())
	{
		input = StringManipulator::alltrim(input);

		if(StringManipulator::isNumber(input))
		{
			input = StringManipulator::removeLeadingZeros(input);

			number = input;

			std::array<VecNumber<DTYPE>, 3> result;
			if (Solver<DTYPE>::solve(number, result/*, true*/))
			{
				std::cout << "Number of 3k+1 operations: " << result[0] << std::endl;
				std::cout << "Number of 2k operations: " << result[1] << std::endl;
				std::cout << "Maximum member: " << result[2] << std::endl;
				std::cout << std::endl;
			}
		}

		std::cout << "Number: ";
	}

	//system("pause");

	return 0;
}