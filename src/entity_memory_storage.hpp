#include <string>
#include "lib/event/EventBus.cpp"

// Include Crow so that we can use its request/response data types.
/// #include "lib/crow_all.h"



// Inherit from EventBus.
class EntityMemoryStorage : EventEmitter
{
private:
  int count{ 0 };
  std::string response{ "hi there" };

public:
  std::string respond();
};