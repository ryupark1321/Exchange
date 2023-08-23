#include <memory>
#include <vector>
#include <deque>
#include "order.hpp"
#pragma once

class AggregateOrder {
  public:
    AggregateOrder(std::shared_ptr<Order> order);
    AggregateOrder(std::vector<std::shared_ptr<Order>>& newOrders);
    ~AggregateOrder();
    void update();
    void add(std::shared_ptr<Order> order);
    void clear();
    float price;
    std::deque<std::shared_ptr<Order>>& orders = orders_;
    int current_order_quantity;

  private:
    std::deque<std::shared_ptr<Order>> orders_;
    int current_size_;
};