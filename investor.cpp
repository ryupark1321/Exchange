#include <memory>
#include "order.hpp"
#include "investor.hpp"

Investor::Investor(std::string name, std::vector<std::array<int, 2>> priceAndShare) {
  name_ = name;
}

std::shared_ptr<Order> Investor::bid(std::shared_ptr<Stock> targetStock, int shares, int pricePerShare) {
  std::shared_ptr<Order> order = std::make_shared<Order>(priceperShare, shares, 0, target);
  activeOrders.emplace_back(order);
  return activeOrders;
}

void purchasedStock(std::shared_ptr<Order> fill, int quantity) {
  if (stockMap_.find(fill.stock) == stockMap_.end()) {
    stockMap_[fill.stock] = 0;
  }
  stockMap_[fill.stock] += fill.quantity;
}

std::shared_ptr<Order> Investor::ask(std::shared_ptr<Stock> targetStock, int shares, int askPrice) {
  return std::make_shared<Order>(priceperShare, shares, 1, target);
}

void soldStock(std::shared_ptr<Order> fill) {
  if (stockMap_.find(fill.stock) == stockMap_.end() || stockMap_[fill.stock] < fill.quantity) {
    throw new error("No stock to be sold: concurrency error suspected.")
  } 
  stockMap_[fill.stock] -= fill.quantity;
}
