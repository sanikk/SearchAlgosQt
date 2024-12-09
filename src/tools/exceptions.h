#include <sstream>
#include <stdexcept>


class VerboseException : public std::runtime_error {
  std::ostringstream message;
public:
  VerboseException(std::string i_message);
  void add_to_message(std::string part);
  void add_to_message(int part);
  std::string str();
};
