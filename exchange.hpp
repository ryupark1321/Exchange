#include "orderbook.hpp"
#include "stock.hpp"
#include <map>
#include <memory>
#include <vector>

// Singleton
class Exchange {
  public:
    static Exchange& getInstance();
    void processOrderBookAndStockCreationMessage(const std::string& msg);
    void processOrdersMessage(const std::string& ordersMsg);
    void update();
    static Exchange *exchange;
    int index = 0;

  private:
    static std::map<int, std::shared_ptr<Engine>> intToEngine;
    Exchange();
    std::map<std::shared_ptr<Stock>, std::shared_ptr<OrderBook>> bookMap_;
};