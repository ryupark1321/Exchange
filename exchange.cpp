#include "engine.cpp"
#include "exchange.hpp"
#include "orderbook.hpp"

Exchange Exchange::exchange;

Exchange::Exchange() {
  
}

Exchange& Exchange::getInstance() {
  return exchange;
}

void Exchange::update() {
  return;
}