#include "orderbook.hpp"
#include "aggregateorder.hpp"

OrderBook::OrderBook(std::shared_ptr<Stock> st, std::shared_ptr<Engine> eg): 
engine_{eg},
stock_{st}
{}

void OrderBook::addToBook(std::map<float, std::shared_ptr<AggregateOrder>>& map, std::vector<std::shared_ptr<AggregateOrder>>& book, std::shared_ptr<Order>& order) {
  if (map.find(order->price) == map.end()) {
    map[order->price] = std::make_shared<AggregateOrder>(order);       
    book.push_back(map[order->price]);
  } else {
    map[order->price]->add(order);
  }
}

void OrderBook::addOrder(const std::string& msg) {
  std::array<std::string, 4> order_detail;
  parseOrderString(order_detail, msg);
  // add Orders
  std::shared_ptr<Order> order = std::make_shared<Order>(std::stof(order_detail[2]),std::stof(order_detail[3]),std::stoi(order_detail[1]),stock_);
  match(order);
  if (order->quantity > 0){
    if (order->side == 1) {
      addToBook(sellMap_, sell_, order);
    } else {
      addToBook(buyMap_, buy_, order);
    }
    sort();
  }
  stock_->updatePrice(order->price);
}

std::string OrderBook::to_string() {
  std::string buys("Buys");
  for (auto& buy : buy_) {
    buys += "\n" + std::to_string(buy->price) + " : " + std::to_string(buy->current_order_quantity);
  }
  buys += "\n";
  std::string sells("Sells");
  for (auto& sell : sell_) {
    sells += "\n" + std::to_string(sell->price) + " : " + std::to_string(sell->current_order_quantity);
  }
  sells += "\n";
  return buys + sells;
}

void OrderBook::matchHelper(std::shared_ptr<Order>& order, std::vector<std::shared_ptr<AggregateOrder>>& book) {
  int idx = 0;
  const auto& itr = book.begin();
  auto end = book.end();
  while (itr + idx != end && (*(itr + idx))->price >= order->price && order->quantity > 0) {
    engine_->match(order, *(itr + idx));
    if ((*(itr + idx))->current_order_quantity == 0) {
        book.erase(itr + idx++);
      }
  }
}

void OrderBook::match(std::shared_ptr<Order>& order) {
  if (static_cast<int>(order->side)) {
    matchHelper(order, buy_);
  } else {
    matchHelper(order, sell_);
  }
}

// There should be multiple orders in this string
void OrderBook::parseOrderString(std::array<std::string, 4>& output, const std::string& orderString) {
  int previous_idx = 0, idx = 0;
  // Stock Side Price Quantity
  for (int current_idx = 0; current_idx < orderString.length(); current_idx++) {
    if (orderString[current_idx] == ' ') {
      output[idx++] = orderString.substr(previous_idx, current_idx - previous_idx);
      previous_idx = current_idx + 1;
    }
  }
  output[idx] = orderString.substr(previous_idx);
}