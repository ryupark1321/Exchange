#include <memory>
#include <time.h>
#include "stock.hpp"
#pragma once

class Order {
  public:
    enum OrderSide {
      Buy = 0,
      Sell = 1
    };

    static OrderSide toOrderSide(int order_side) {return order_side? OrderSide::Sell : OrderSide::Buy;};

    static std::string orderSideToString(OrderSide& os) {return static_cast<int>(os)? "Sell" : "Buy";};

    Order(float p, float q, int os, std::shared_ptr<Stock>& st):
      price_(p),
      quantity_(q),
      side_(Order::toOrderSide(os)),
      stock_(st){};

    bool isExpired() {return difftime(order_placed_time, time(0)) >= 86400;};

    std::string to_string();

    time_t& order_placed_time = order_placed_time_;    
    float& price = price_;
    float& quantity = quantity_;
    float& original_quantity = original_quantity_;
    OrderSide& side = side_;
    std::shared_ptr<Stock>& stock = stock_;
  private:
    float price_;
    float quantity_;
    float original_quantity_;
    OrderSide side_;
    std::shared_ptr<Stock> stock_;
    time_t order_placed_time_ = time(0);    
};