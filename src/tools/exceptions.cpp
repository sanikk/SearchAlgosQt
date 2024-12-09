#include "exceptions.h"

VerboseException::VerboseException(std::string i_message) : message(i_message), std::runtime_error(i_message) {
  
}

void VerboseException::add_to_message(std::string part) {
  message << part;
}

void VerboseException::add_to_message(int part) {
  message << part;
}

std::string VerboseException::str() {
  return message.str();
}

