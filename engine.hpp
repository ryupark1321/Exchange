#include <memory>
#include <vector>
#include "aggregateorder.hpp"
#pragma once

// Matching Algorithm
// Every participant gets the best possible execution at the fairest price
// Lesson: Aggregate quantities for the same price

// FIFO
// Price - Time Priority
// Same Price than earlier one gets filled first
// Remaining order loses priority when price/quantity/account number change

// FIFO with LMM
// LMM takes their designated percentage first, than FIFO

// Pro Rata
// Price Quantity Time Priority
// Same Price but Quantity gets more 
// Round down when allocating based on quantity, than remaining by FIFO

// Configurable
// Pass1 - FIFO (certain portion only)
// Pass2 - Pro Rata (then rest of the portion)
// Pass2.5 - Leveling pass on 1-lot levelling (get 1 unit, still on pro-rata excluding those who got em before)
// Final - FIFO ()

// Threshold Pro Rata(TOP)
// When the aggressing order hits the order book, TOP receives the first allocation - to the maximum configured priority
// Meet the minimum quantity "threshold" to receive allocation in the Pro Rata round
// First one for the price level gets the TOP status
// Top has min/max allocation lots
// Than fifo
// (Top - Pro Rata - FIFO)

// Threshold Pro Rata with LMM(TOPLMM)
// Top - LMM - Pro Rata - FIFO (for remaining)


// Allocation
// Top - Pro Rata with minimum 2 lots - FIFO residual

class Engine {
  public:
    virtual void fifo(std::array<std::shared_ptr<AggregateOrder>, 2> &aggregateOrders) {
      auto& buyOrders = aggregateOrders[0];
      auto& sellOrders = aggregateOrders[1];
      auto buyItr = buyOrders->orders.rbegin();
      auto sellItr = sellOrders->orders.rbegin();
      while (sellOrders->current_order_quantity > 0 && buyOrders->current_order_quantity > 0 && sellItr != sellOrders->orders.rend() && buyItr != buyOrders->orders.rend()) {
        if ((*buyItr)->quantity > (*sellItr)->quantity) {
          sellOrders->current_order_quantity -= (*sellItr)->quantity;
          buyOrders->current_order_quantity -= (*sellItr)->quantity;
          (*buyItr)->quantity -= (*sellItr)->quantity;
          (*sellItr)->quantity = 0;
          sellItr++;
          sellOrders->orders.pop_back();
        } else {
          buyOrders->current_order_quantity -= (*buyItr)->quantity;
          sellOrders->current_order_quantity -= (*buyItr)->quantity;
          (*sellItr)->quantity -= (*buyItr)->quantity;
          (*buyItr)->quantity = 0;
          buyItr++;
          buyOrders->orders.pop_back();
        }
        if ((*sellItr)->quantity == 0){
          sellItr++;
          sellOrders->orders.pop_back();
        }
      }
    }
    virtual void match(std::array<std::shared_ptr<AggregateOrder>, 2> &aggregateOrders) {}
};