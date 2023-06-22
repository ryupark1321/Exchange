#include "stock.hpp"

int Stock::current_id = 0;

Stock::Stock() {
  id_ = Stock::current_id++;
}

Stock::Stock(std::string stock_name, float stock_price, time_t update_time) {
  id_ = Stock::current_id++;
  name_ = stock_name;
  price_ = stock_price;
  last_updated_ = update_time;
}

bool Stock::updatePrice(float new_price) {
  if (difftime(time(0), last_updated) > 0) {
    price_ = new_price;
    return true;
  }
  return false;
}

std::string Stock::toString() {
  return name_ + " " + std::to_string(price_) + " " + ctime(&last_updated_);
}

Stock& Stock::operator=(const Stock& st) {
  name_ = st.name_;
  price_ = st.price_;
  id_ = st.id_;
  last_updated_ = st.last_updated_;
  return *this;
}