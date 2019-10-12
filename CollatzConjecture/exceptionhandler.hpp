#pragma once

#include <vector>
#include <stdexcept>

namespace ExceptionHandler
{
	template<class T>
	bool push_back(std::vector<T> & object, T pushObject)
	{
		try
		{
			object.push_back(pushObject);

			//ExceptionHandler::insert(object, pushObject, object.end());
		}
		catch(const std::exception &)
		{
		}
		catch(...)
		{
		}

		return false;
	}

	template<class T>
	bool insert(std::vector<T> & object, T & insertObject, typename std::vector<T>::iterator it)
	{
		try
		{
			object.insert(it, insertObject);

			return true;
		}
		catch(const std::exception &)
		{
		}
		catch(...)
		{
		}

		return false;
	}
}