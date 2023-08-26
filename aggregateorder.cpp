#include "aggregateorder.hpp"
#include "order.hpp"
#include <time.h>

AggregateOrder::AggregateOrder(std::shared_ptr<Order> order) {
  price = order->price;
  orders_.push_front(order);
  current_size_ = 1;
  current_order_quantity = order->quantity;
}

// Assumes the input vector is sorted in terms of time from oldest to newest
AggregateOrder::AggregateOrder(std::vector<std::shared_ptr<Order>>& newOrders) {
  current_size_ = 0;
  current_order_quantity = 0;
  for (auto& order: newOrders) {
    orders_.push_front(order);
    current_size_++;
    current_order_quantity += order->quantity;
  }
}

AggregateOrder::~AggregateOrder() {
  clear();
}

bool isExpired(time_t& t, time_t& now) {return !(t > now - 86400);}

void AggregateOrder::update() {
  auto itr = orders_.rbegin();
  time_t now = time(0);
  while (itr != orders_.rend() && !isExpired((*itr)->order_placed_time, now)) {
    current_order_quantity -= (*itr)->quantity;
    itr++;
    orders_.pop_back();
    current_size_--;
  }
}

void AggregateOrder::clear() {
  for (auto& order: orders) {
    order->quantity = 0;
  }
  orders_.clear();
  current_size_ = 0;
  current_order_quantity = 0;
}

void AggregateOrder::add(std::shared_ptr<Order> order) {
  orders_.push_front(order);
  current_size_++;
  current_order_quantity += order->quantity;
}