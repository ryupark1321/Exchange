#include "engine.hpp"
#include "fifo.cpp"
#include "exchange.hpp"
#include "orderbook.hpp"
#include "stock.hpp"
#include <stdexcept>

Exchange::Exchange() {}

std::map<int, std::shared_ptr<Engine>> Exchange::intToEngine = {
  {0, std::make_shared<Engine>(FIFO())}
};

// Should handle a line
// Message should be in the form of
// Stock Price Quantity Time MatchingAlgo
void Exchange::processOrderBookAndStockCreationMessage(const std::string& message) {
  int space_idx = 0, prev_idx = 0, idx = 0;
  std::array<std::string, 5> strArr;
  while ((space_idx = message.find(' ', prev_idx)) > -1) {
    strArr[idx] = message.substr(prev_idx, space_idx);
    prev_idx = space_idx + 1;
    idx++;
  }
  int algo_num = 0;
  if (strArr.size() != 5 || ((algo_num = std::stoi(strArr[4])) >= Exchange::intToEngine.size())) {
    throw std::invalid_argument("Invalid algorithm type");
  }
  std::shared_ptr<Stock> newStock = Stock::getStockPtr(strArr[0], std::stof(strArr[1]), std::stoi(strArr[2]), (time_t)std::stoi(strArr[3]));
  std::shared_ptr<Engine> engPtr = Exchange::intToEngine[std::stoi(strArr[4])];
  std::shared_ptr<OrderBook> orderBookPtr = std::make_shared<OrderBook>(newStock, engPtr);
  bookMap_[newStock] = orderBookPtr;
}

void Exchange::processOrdersMessage(const std::string& ordersMsg) {
  std::string stockStr = ordersMsg.substr(0, ordersMsg.find(' '));
  bookMap_[Stock::stockAbbrvMap[stockStr]]->addOrders(ordersMsg);
}

Exchange* Exchange::exchange = nullptr;

Exchange& Exchange::getInstance() {
  if (!exchange) {
    exchange = new Exchange();
  }
  return *exchange;
}

void Exchange::update() {
  return;
}