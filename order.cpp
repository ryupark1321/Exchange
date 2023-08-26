#include "order.hpp"

std::string Order::to_string() {
  return Order::orderSideToString(side_) + " Order for " + std::to_string(quantity_) + " shares at price " + std::to_string(price_) + " at time " + ctime(&order_placed_time);
}
