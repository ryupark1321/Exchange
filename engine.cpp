#include "engine.hpp"

void Engine::fifo(std::shared_ptr<Order>& order, std::shared_ptr<AggregateOrder>& aggregateOrder) {
  auto& orders = aggregateOrder->orders;
  auto itr = orders.rbegin();
  while (aggregateOrder->current_order_quantity > 0 && itr != orders.rend() && order->quantity > 0) {
    if ((*itr)->quantity > order->quantity) {
      aggregateOrder->current_order_quantity -= order->quantity;
      (*itr)->quantity -= order->quantity;
      order->quantity = 0;
    } else {
      aggregateOrder->current_order_quantity -= (*itr)->quantity;
      order->quantity -= (*itr)->quantity;
      (*itr)->quantity = 0;
      itr++;
      orders.pop_back();
    }
  }
}

void fifoProRata(std::shared_ptr<Order>& order, std::shared_ptr<AggregateOrder>& aggregateOrder) {
  auto& orders = aggregateOrder->orders;
  auto itr = orders.rbegin();
  while (itr != orders.rend() && order->quantity > 0) {
    if (order->quantity >= (*itr)->quantity) {
      order->quantity -= (*itr)->quantity;
      (*itr)->quantity = 0;
      orders.pop_back();
    } else {
      (*(itr++))->quantity -= order->quantity;
      order->quantity = 0;
    }
  }
}

int proRataHelper(std::shared_ptr<Order>& order, std::shared_ptr<AggregateOrder>& aggregateOrder, int orderQuantity) {
  auto& orders = aggregateOrder->orders;
  auto itr = orders.begin();
  int dispatched_shares = 0;
  while (itr != orders.end() && order->quantity > 0) {
    int shares = (*itr)->quantity/aggregateOrder->current_order_quantity * orderQuantity;
    dispatched_shares += shares;
    (*itr)->quantity -= shares;
    order->quantity -= shares;
    if ((*itr)->quantity == 0) {
      orders.erase(itr++);
    }
  }
  aggregateOrder->current_order_quantity -= dispatched_shares;
  return dispatched_shares;
}

void Engine::prorata(std::shared_ptr<Order>& order, std::shared_ptr<AggregateOrder>& aggregateOrder) {
  if (order->quantity >= aggregateOrder->current_order_quantity) {
    order->quantity -= aggregateOrder->current_order_quantity;
    aggregateOrder->clear();
    return;
  } 
  int dispatched_shares = proRataHelper(order, aggregateOrder, order->quantity);
  fifoProRata(order, aggregateOrder);
}

void Engine::match(std::shared_ptr<Order>& order, std::shared_ptr<AggregateOrder>& aggregateOrder) {
  switch(match_algo_number) {
    case 0:
      prorata(order, aggregateOrder);
      break;
    default:
      fifo(order, aggregateOrder);
  }
}