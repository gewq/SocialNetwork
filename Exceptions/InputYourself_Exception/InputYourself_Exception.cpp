#include "InputYourself_Exception.h"



InputYourself_Exception::InputYourself_Exception(const std::string& errorMessage):
  std::exception()
{
  errorMessage_ += "Error: Input node is yourself! " + errorMessage;
}



const char* InputYourself_Exception::what() const noexcept
{
  return errorMessage_.c_str();
}