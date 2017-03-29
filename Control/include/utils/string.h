#pragma once

#include <string>
#include <vector>


namespace utils
{
/**
  * This namespace contains string utilities.
  */
namespace string
{

/**
  * This function splits a string by any of given delimiters.
  * @param[in] str - string to split.
  * @param[in] delimiters - a set of delimiters to split by.
  * @return a container of the split parts.
  */
std::vector<std::string> Split(const std::string& str,
                               const std::string&& delimiters);

/**
  * Use this function to find out whether a string contains only digits.
  * @param[in] str - string to check.
  * @return If string is made of digits, true is returned.
  *         Otherwise, false is returned.
  */
bool IsNumber(const std::string& str);

}
}
