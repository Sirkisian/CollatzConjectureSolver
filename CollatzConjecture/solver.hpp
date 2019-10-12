#pragma once

#include <array>
#include "vecnumber.hpp"

//Template class for solving of Collatz Conjecture
//return value is odd count, even count and maximum member
template <class T>
class Solver
{
	public:
		static bool solve(const VecNumber<T> & number, std::array<VecNumber<T>, 3> & result, bool show = false);
};