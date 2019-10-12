#pragma once

#include <string>
#include <algorithm>
#include <regex>

class StringManipulator
{
	public:
		static std::string ltrim(const std::string & string);
		static std::string rtrim(const std::string & string);
		static std::string alltrim(const std::string & string)
		{
			return StringManipulator::rtrim(StringManipulator::ltrim(string));
		}

		static bool isNumber(const std::string & string);
		static bool match(const std::string & string, std::string regex);

		static std::string removeLeadingZeros(const std::string & string);
};