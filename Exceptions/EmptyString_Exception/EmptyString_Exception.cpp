#include "EmptyString_Exception.h"



EmptyString_Exception::EmptyString_Exception(const std::string& errorMessage):
  std::exception()
{
  errorMessage_ += "Error: String is empty! " + errorMessage;
}



const char* EmptyString_Exception::what() const noexcept
{
  return errorMessage_.c_str();
}