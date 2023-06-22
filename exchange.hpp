#include "orderbook.hpp"
#include <array>

// Singleton
class Exchange {
  public:
    static Exchange& getInstance();

    void update();

    static Exchange exchange;
    std::vector<OrderBook> buy_books;
    std::vector<OrderBook> sell_books;
    int index = 0;
  private:
    Exchange();
};