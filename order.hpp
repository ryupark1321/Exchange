#include <memory>
#include <time.h>
#include "stock.hpp"

class Order {
  public:
    enum OrderSide {
      Buy = 0,
      Sell = 1
    };

    static OrderSide toOrderSide(bool order_side) {return order_side? OrderSide::Buy : OrderSide::Sell;};

    static std::string orderSideToString(OrderSide& os) {return static_cast<int>(os)? "Sell" : "Buy";};

    Order(float p, float q, bool os, std::shared_ptr<Stock> st);

    bool isExpired() {return difftime(order_placed_time, time(0)) >= 86400;};

    std::string to_string();

    time_t& order_placed_time = time(0);    
    float& price = price_;
    float& quantity = quantity_;
    OrderSide& side = side_;
    std::shared_ptr<Stock> stock = stock_;

  private:
    float price_;
    float quantity_;
    OrderSide side_;
    std::shared_ptr<Stock> stock_;
};