#include "order.hpp"

Order::Order(float p, float q, bool os, Stock& st) {
  price_ = p;
  quantity_ = q;
  side_ = Order::toOrderSide(os);
  stock_ = st;
}

Order::OrderSide Order::toOrderSide(bool order_side) {
  if (order_side) {
    return OrderSide::Buy;
  }
  return OrderSide::Sell;
}

std::string Order::orderSideToString(OrderSide& os) {
  if (static_cast<int>(os) == 0) {
    return "Buy";
  }
  return "Sell";
}

bool Order::isExpired() {
  return difftime(order_placed_time, time(0)) >= 86400;
}

std::string Order::to_string() {
  return Order::orderSideToString(side_) + " Order for " + std::to_string(quantity_) + " shares at price " + std::to_string(price_) + " at time " + ctime(&order_placed_time);
}
