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

void OrderBook::addOrders(const std::string& msg) {
  std::vector<std::shared_ptr<Order>> allOrders;
  parseOrderString(allOrders, msg);
  // add Orders
  for (auto& order : allOrders) {
    if (order->side == 1) {
      addToBook(sellMap_, sell_, order);
    } else {
      addToBook(buyMap_, buy_, order);
    }   
  }
  sort();
}

// assume data is sorted
void OrderBook::match() {
  auto buy_itr = buy_.begin();
  auto buy_end = buy_.end();
  auto sell_itr = sell_.rbegin();
  auto sell_end = sell_.rend();
  while (buy_itr != buy_end) {
    while (sell_itr != sell_end) {
      if ((*buy_itr)->price < (*sell_itr)->price) {
        break;
      }
      std::array<std::shared_ptr<AggregateOrder>, 2> aggregateOrders{(*buy_itr), (*sell_itr)};
      engine_->match(aggregateOrders);
      if ((*buy_itr)->current_order_quantity == 0) {
        buy_.erase(buy_itr++);
      }
      if ((*sell_itr)->current_order_quantity == 0) {
        sell_.erase(std::next(sell_itr++).base());
      } 
    }
    if (sell_itr != sell_end) {
      break;
    }
  }
}

// There should be multiple orders in this string, deliminated by \n
void OrderBook::parseOrderString(std::vector<std::shared_ptr<Order>>& orders, const std::string& ordersString) {
  int current_idx = 0, previous_idx = 0;
  while((current_idx = ordersString.find(' ', previous_idx)) > -1) {
    std::array<std::string, 4> parsedOutput;
    parseOrderLine(parsedOutput, ordersString.substr(previous_idx, current_idx - previous_idx));
    orders.emplace_back(std::make_shared<Order>(std::stof(parsedOutput[2]), std::stof(parsedOutput[3]), std::stoi(parsedOutput[1]), stock_));
    previous_idx = ++current_idx;
  }
}

void OrderBook::parseOrderLine(std::array<std::string, 4>& output, const std::string& orderLine) {
  int current_idx = 0, previous_idx = 0, idx = 0;
  // Order String should be in the format of
  // Stock Side Price Quantity
  while ((current_idx = orderLine.find(' ', previous_idx)) > -1) {
    output[idx++] = orderLine.substr(previous_idx, current_idx - previous_idx);
    previous_idx = ++current_idx;
  }
}