#include "engine.cpp"
#include "exchange.hpp"

Exchange Exchange::exchange;

Exchange::Exchange() {}

Exchange& Exchange::getInstance() {
  return exchange;
}

void Exchange::update() {
  return;
}