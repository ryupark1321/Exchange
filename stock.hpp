#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <time.h>

class Stock {
  public:
    Stock(std::string stock_name, float stock_price, int stock_quantity, time_t update_time): 
      numShares{stock_quantity},
      name_{stock_name},
      price_{stock_price},
      id_{Stock::current_id++},
      last_updated_{update_time} {};

    static std::shared_ptr<Stock> getStockPtr(std::string stock_name, float stock_price, int stock_quantity, time_t update_time);

    static std::map<std::string, std::shared_ptr<Stock>> stockAbbrvMap;

    bool updatePrice(float new_price);

    std::string to_string();

    Stock& operator=(const Stock& st);

    static int current_id;
    std::string& name = name_;
    time_t& last_updated = last_updated_;
    int numShares;

  private:
    std::string name_;
    float price_;
    int id_;
    time_t last_updated_;
};