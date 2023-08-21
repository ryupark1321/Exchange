#include "order.hpp"

Order::Order(float p, float q, int os, std::shared_ptr<Stock> st) {
  price_ = p;
  quantity_ = q;
  side_ = Order::toOrderSide(os);
  stock_ = st;
}

std::string Order::to_string() {
  return Order::orderSideToString(side_) + " Order for " + std::to_string(quantity_) + " shares at price " + std::to_string(price_) + " at time " + ctime(&order_placed_time);
}
