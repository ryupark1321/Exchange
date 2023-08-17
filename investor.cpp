#include "investor.hpp"

Investor::Investor(std::string name, std::vector<std::array<int, 2>> priceAndShare) {
  name_ = name;
}

void Investor::bid(std::shared_ptr<Stock> targetStock, int shares, int pricePerShare) {
  // Create Order
  // Add to Orderbook
  return;
}

void Investor::purchaseStock(std::shared_ptr<Order> fill) {
  return;
}

void Investor::ask(std::shared_ptr<Stock> targetStock, int shares, int askPrice) {
  return;
}

void sellStock(std::shared_ptr<Order> fill) {
  return;
}
