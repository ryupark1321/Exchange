#include "engine.hpp"
#include "exchange.hpp"
#include <stdexcept>

Exchange::Exchange() {}

std::map<int, std::shared_ptr<Engine>> Exchange::intToEngine = {
  {0, std::make_shared<Engine>(-1)},
  {1, std::make_shared<Engine>(0)}
};

// Should handle a line
// Message should be in the form of
// Stock Price Quantity Time MatchingAlgo
void Exchange::processOrderBookAndStockCreationMessage(const std::string& message) {
  int prev_idx = 0, idx = 0;
  std::array<std::string, 5> strArr;
  for (int space_idx = 0; space_idx < (int) message.length(); space_idx++) {
    if (message[space_idx] == ' ') {
      strArr[idx++] = message.substr(prev_idx, space_idx - prev_idx);
      prev_idx = space_idx + 1;
    }
  }
  strArr[idx] = message[prev_idx];
  int algo_num = 0;
  if (strArr.size() != 5 || ((algo_num = std::stoi(strArr[4])) >= Exchange::intToEngine.size())) {
    throw std::invalid_argument("Invalid algorithm type");
  }
  std::shared_ptr<Stock> newStock = std::make_shared<Stock>(strArr[0], std::stof(strArr[1]), std::stoi(strArr[2]), (time_t)std::stoi(strArr[3]));
  Stock::stockAbbrvMap[strArr[0].substr(0,3)]=newStock;
  std::shared_ptr<Engine> engPtr = Exchange::intToEngine[std::stoi(strArr[4])];
  std::shared_ptr<OrderBook> orderBookPtr = std::make_shared<OrderBook>(newStock, engPtr);
  bookMap_[newStock] = orderBookPtr;
}

void Exchange::processOrderMessage(const std::string& orderMsg) {
  int idx = 0;
  while (orderMsg[idx] != ' ') {
    idx++;
  }
  std::string stockStr = orderMsg.substr(0, idx);
  bookMap_[Stock::stockAbbrvMap[stockStr]]->addOrder(orderMsg);
}

std::string Exchange::to_string() {
  std::string exchange("Exchange");
  for (auto& book: bookMap_) {
    exchange += "\n" + book.first->to_string() + " : " + book.second->to_string();
  }
  return exchange;
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