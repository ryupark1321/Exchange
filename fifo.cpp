#include "engine.hpp"
#include <memory>
#include <vector>
#include "aggregateorder.hpp"
#include "order.hpp"

class FIFO : public Engine {
  public:
    FIFO() {}

    void match(std::array<std::shared_ptr<AggregateOrder>, 2> &aggregateOrders) override {
      fifo(aggregateOrders);
    }
};