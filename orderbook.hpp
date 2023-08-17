#include "engine.hpp"
#include "order.hpp"
#include <memory>
#include <queue>

class OrderBook {  

  private:
    std::shared_ptr<Engine> me_;
    std::shared_ptr<Stock> stock_;
    std::priority_queue<std::shared_ptr<Order>, std::vector<std::shared_ptr<Order>>, > book_;
};