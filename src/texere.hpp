#include <string>

#ifndef _SRC_EVENT_OBJECT_HPP_
#define _SRC_EVENT_OBJECT_HPP_


// Inherit from EventBus.
class Texere {

  int count{ 0 };

  public:
  Texere(); // Basic constructor
  virtual ~Texere();  // Basic destructor
  Texere (const Texere& other); // Basic copy constructor
  
  std::string respond(std::string input) {
    return std::string{ "hey man," };
  }
};

#endif /* _SRC_EVENT_OBJECT_HPP_ */