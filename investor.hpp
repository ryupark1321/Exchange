#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "stock.hpp"
#include "order.hpp"

class Investor {
  public:
    Investor(std::string name) {
      name_ = name;
    };

    // desiredStock, shares
    Investor(std::string name, std::vector<std::array<int, 2>> priceAnstd::shared_ptr<Stock> targetStock, int shares, int pricePerShare);

    void bid(std::shared_ptr<Stock> targetStock, int shares, int pricePerShare);

    void purchaseStock(std::shared_ptr<Order> fill);

    void ask(std::shared_ptr<Stock> targetStock, int shares, int askPrice);

    void sellStock(std::shared_ptr<Stock> targetStock, int shares, int askPrice);

  private:
    std::string name_;
    std::map<std::shared_ptr<Stock>, int> stockMap_;
};