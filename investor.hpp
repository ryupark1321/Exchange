#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "stock.hpp"
#include "order.hpp"

class Investor {
  public:
    Investor(std::string name) {name_ = name;};

    // desiredStock, shares
    // Investor(std::string name, std::vector<std::array<shared_ptr<Stock>, std::array<float, int>>>, int shares, int pricePerShare);

    std::shared_ptr<Order>& bid(std::shared_ptr<Stock> targetStock, int shares, float pricePerShare);

    void purchasedStock(std::shared_ptr<Order> fill);

    std::shared_ptr<Order> ask(std::shared_ptr<Stock> targetStock, int shares, float askPrice);

    void soldStock(std::shared_ptr<Order> fill);

    std::vector<std::shared_ptr<Order>>& activeOrders = activeOrders_;
    std::map<std::shared_ptr<Stock>, int>& stockMap = stockMap_;

  private:
    std::string name_;
    std::vector<std::shared_ptr<Order>> activeOrders_;
    std::map<std::shared_ptr<Stock>, int> stockMap_;
};