#include "stock.hpp"

int Stock::current_id = 0;

std::map<std::string, std::shared_ptr<Stock>> Stock::stockAbbrvMap;

std::shared_ptr<Stock> Stock::getStockPtr(std::string stock_name, float stock_price, int stock_quantity, time_t update_time) {
  std::shared_ptr<Stock> stPtr = std::make_shared<Stock>(stock_name, stock_price, stock_quantity, update_time);
  Stock::stockAbbrvMap[stock_name.substr(0,3)] = stPtr;
  return stPtr;
}

bool Stock::updatePrice(float new_price) {
  if (difftime(time(0), last_updated) > 0) {
    price_ = new_price;
    last_updated = time(0);
    return true;
  }
  return false;
}

std::string Stock::to_string() {
  return name_ + " " + std::to_string(price_) + " " + ctime(&last_updated_);
}

Stock& Stock::operator=(const Stock& st) {
  name_ = st.name_;
  price_ = st.price_;
  id_ = st.id_;
  last_updated_ = st.last_updated_;
  return *this;
}