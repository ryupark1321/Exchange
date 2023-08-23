#include "engine.hpp"
#include "aggregateorder.hpp"
#include <algorithm>
#include <memory>
#include <vector>
#pragma once

class OrderBook {
  public:
    OrderBook(std::shared_ptr<Stock> st, std::shared_ptr<Engine> eg);

    // Invariant: Orders are for the same stock
    void addOrders(const std::string& msg);

    void match();

  private:
    void addToBook(std::map<float, std::shared_ptr<AggregateOrder>>& map, std::vector<std::shared_ptr<AggregateOrder>>& book, std::shared_ptr<Order>& order);

    void parseOrderString(std::vector<std::shared_ptr<Order>>& orders, const std::string& ordersString);

    void parseOrderLine(std::array<std::string, 4>& output, const std::string& orderLine);

    class PriceCompare {
      public:
        bool operator()(std::shared_ptr<AggregateOrder>& ao1, std::shared_ptr<AggregateOrder>& ao2) {
          return ao1->price > ao2->price;
        }
    };
    
    void sort(){
      std::sort(buy_.begin(), buy_.end(), PriceCompare());
      std::sort(sell_.begin(), sell_.end(), PriceCompare());
    };

    std::shared_ptr<Engine> engine_;
    std::shared_ptr<Stock> stock_;
    std::map<float, std::shared_ptr<AggregateOrder>> buyMap_;
    std::map<float, std::shared_ptr<AggregateOrder>> sellMap_;
    std::vector<std::shared_ptr<AggregateOrder>> buy_;
    std::vector<std::shared_ptr<AggregateOrder>> sell_;
};