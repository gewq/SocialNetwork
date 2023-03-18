#include "EmptyObject_Exception.h"



EmptyObject_Exception::EmptyObject_Exception(const std::string& errorMessage):
  std::exception()
{
  errorMessage_ += "Error: Node is empty! " + errorMessage;
}



const char* EmptyObject_Exception::what() const noexcept
{
  return errorMessage_.c_str();
}