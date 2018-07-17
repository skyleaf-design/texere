#include <string>
// #include <boost/signal2.hpp>



class EntityMemoryStorage
{
private:
  int count{ 0 };
  std::string response{ "hi there" };

public:
  std::string respond();
};