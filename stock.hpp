#pragma once
#include <string>
#include <time.h>

class Stock {
  public:
    Stock();

    Stock(std::string stock_name, float stock_price, time_t update_time);

    bool updatePrice(float new_price);

    std::string toString();

    Stock& operator=(const Stock& st);

    static int current_id;
    std::string& name = name_;
    time_t& last_updated = last_updated_;

  private:
    std::string name_;
    float price_;
    int id_;
    time_t last_updated_;
};