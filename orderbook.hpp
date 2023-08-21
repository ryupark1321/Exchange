#include "engine.hpp"
#include "aggregateorder.hpp"
#include <memory>
#include <queue>

class OrderBook {  
  public:
    OrderBook(std::shared_ptr<Stock> st, std::shared_ptr<Engine> eg);

    // Decide on types
    int addOrders();


  private:
    std::shared_ptr<Engine> engine_;
    std::shared_ptr<Stock> stock_;
    std::priority_queue<std::shared_ptr<Order>, std::vector<std::shared_ptr<Order>>> book_;
};