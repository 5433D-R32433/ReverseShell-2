#include "utils/string.h"

#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>


std::vector<std::string>
utils::string::Split(
	const std::string& str,
	const std::string&& delimiters)
{
	std::vector<std::string> parts;
    boost::split(parts, str, boost::is_any_of(delimiters));

	return ( parts );
}

bool
utils::string::IsNumber(
	const std::string& str)
{
	return ( !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit) );
}
