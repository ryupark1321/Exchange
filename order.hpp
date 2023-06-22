#include <time.h>
#include "stock.hpp"

class Order {
  public:
    enum OrderSide {
      Buy = 0,
      Sell = 1
    };

    static OrderSide toOrderSide(bool order_side);

    static std::string orderSideToString(OrderSide& os);

    Order(float p, float q, bool os, Stock& st);

    bool isExpired();

    std::string to_string();

    const time_t& order_placed_time = time(0);    
    float& price = price_;
    float& quantity = quantity_;
    OrderSide& side = side_;
    Stock& stock = stock_;

  private:
    float price_;
    float quantity_;
    OrderSide side_;
    Stock stock_;
};