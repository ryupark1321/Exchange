#include "engine.hpp"
#include <memory>

class FIFOEngine : public Engine {
  public: 
    bool operator()(std::shared_ptr<Order>& a, std::shared_ptr<Order>& b) {
      return a->order_placed_time > b->order_placed_time;
    }
}