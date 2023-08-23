#include <memory>
#include <stdexcept>
#include "order.hpp"
#include "investor.hpp"

// Investor(std::string name, std::shared_ptr<Stock> targetStock, int shares, int pricePerShare) {
//   name_ = name;

// }

std::shared_ptr<Order>& Investor::bid(std::shared_ptr<Stock> targetStock, int shares, float pricePerShare) {
  std::shared_ptr<Order> order = std::make_shared<Order>(pricePerShare, shares, 0, targetStock);
  activeOrders.emplace_back(order);
  return activeOrders.back();
}

void Investor::purchasedStock(std::shared_ptr<Order> fill) {
  if (stockMap.find(fill->stock) == stockMap.end()) {
    stockMap[fill->stock] = 0;
  }
  stockMap[fill->stock] += (fill->original_quantity - fill->quantity);
}

std::shared_ptr<Order> Investor::ask(std::shared_ptr<Stock> targetStock, int shares, float askPrice) {
  return std::make_shared<Order>(askPrice, shares, 1, targetStock);
}

void Investor::soldStock(std::shared_ptr<Order> fill) {
  if (stockMap.find(fill->stock) == stockMap.end() || stockMap[fill->stock] < fill->original_quantity) {
    throw std::invalid_argument("No stock to be sold: concurrency error suspected.");
  } 
  stockMap[fill->stock] -= (fill->original_quantity - fill->quantity);
}
