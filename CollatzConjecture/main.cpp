#include <chrono>
#include <mutex>
#include <thread>
#include "stringmanipulator.hpp"
#include "solver.hpp"

#define DTYPE int
//#define DTYPE char
//#define DTYPE unsigned int
//#define DTYPE unsigned char

std::mutex coutLock;

void threadPrint(const bool & printLoop);
void threadSolve(const VecNumber<DTYPE> & number, bool & printLoop);

int main()
{
	bool printLoop;
	std::string input;
	VecNumber<DTYPE> number;

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

			printLoop = true;
			std::thread solve(threadSolve, std::ref(number), std::ref(printLoop));
			std::thread print(threadPrint, std::ref(printLoop));

			solve.join();
			print.join();
		}

		std::cout << "Number: ";
	}

	//system("pause");

	return 0;
}

void threadPrint(const bool & printLoop)
{
	while(true)
	{
		coutLock.lock();
		if(printLoop)
		{
			std::cout << ".";
		}
		else
		{
			coutLock.unlock();

			break;
		}
		coutLock.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void threadSolve(const VecNumber<DTYPE> & number, bool & printLoop)
{
	std::array<VecNumber<DTYPE>, 3> result;

	bool solved = Solver<DTYPE>::solve(number, result);

	std::lock_guard<std::mutex> lock(coutLock);
	printLoop = false;
	std::cout << "\r";

	if(solved)
	{
		std::cout << "Number of 3k+1 operations: " << result[0] << std::endl;
		std::cout << "Number of 2k operations: " << result[1] << std::endl;
		std::cout << "Maximum member: " << result[2] << std::endl;
		std::cout << std::endl;
	}
}