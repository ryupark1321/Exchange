#include <memory>
#include "order.hpp"

class Engine {
  public:
    virtual bool operator()(std::shared_ptr<Order>& a, std::shared_ptr<Order>& b) {return false;}
}