#include "stringmanipulator.hpp"

std::string StringManipulator::ltrim(const std::string & string)
{
	std::string lTrimed = string;

	lTrimed.erase(lTrimed.begin(), std::find_if(lTrimed.begin(), lTrimed.end(), [](const char & c){ return !std::isspace(c); }));

	return lTrimed;
}

std::string StringManipulator::rtrim(const std::string & string)
{
	std::string rTrimed = string;

	rTrimed.erase(std::find_if(rTrimed.rbegin(), rTrimed.rend(), [](const char & c){ return !std::isspace(c); }).base(), rTrimed.end());

	return rTrimed;
}

bool StringManipulator::isNumber(const std::string & string)
{
	return StringManipulator::match(string, "[0-9]+");
}

bool StringManipulator::match(const std::string & string, std::string regex)
{
	std::regex regExpression;

	try
	{
		regExpression = regex;
	}
	catch(const std::regex_error &)
	{
		return false;
	}

	return std::regex_match(string, regExpression);
}

std::string StringManipulator::removeLeadingZeros(const std::string & string)
{
	std::string returnValue = string;

	returnValue.erase(0, std::min(returnValue.find_first_not_of('0'), returnValue.size() - 1));

	return returnValue;
}