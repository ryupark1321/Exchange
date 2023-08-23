#include "engine.hpp"
#include <deque>

class ProRata : public Engine {
  public: 
    ProRata() {}

    void fifo(std::deque<std::shared_ptr<Order>>& orders, int dispatched_quantity, int total_quantity) {
      auto fifo_itr = orders.rbegin();
      while (fifo_itr == orders.rend() || dispatched_quantity < total_quantity) {
        dispatched_quantity += (*fifo_itr)->quantity;
        (*fifo_itr)->quantity = 0;
        fifo_itr++;
        orders.pop_back();
      }
    }

    int prorata(std::deque<std::shared_ptr<Order>>& orders, int this_quantity, int target_quantity) {
      auto itr = orders.begin();
      int dispatched_shares = 0;
      while (itr != orders.end()) {
        int shares = (*itr)->quantity/this_quantity * target_quantity;
        dispatched_shares += shares;
        (*itr)->quantity -= shares;
        if ((*itr)->quantity == 0) {
          orders.erase(itr++);
        }
      }
      return dispatched_shares;
    }

    void match(std::array<std::shared_ptr<AggregateOrder>, 2> &aggregateOrders) override {
      auto& buy_orders = aggregateOrders[0];
      auto& sell_orders = aggregateOrders[1];
      int buy_quantity = buy_orders->current_order_quantity;
      int sell_quantity = sell_orders->current_order_quantity;
      if (buy_quantity > sell_quantity) {        
        int dispatched_shares = prorata(buy_orders->orders, buy_quantity, sell_quantity);
        fifo(buy_orders->orders, dispatched_shares, sell_quantity);
        sell_orders->clear();
      } else if (buy_quantity < sell_quantity) { 
        int dispatched_shares = prorata(buy_orders->orders, sell_quantity, buy_quantity);
        fifo(sell_orders->orders, dispatched_shares, buy_quantity);
        buy_orders->clear();
      } else {
        buy_orders->clear();
        sell_orders->clear();
      }
    }
};