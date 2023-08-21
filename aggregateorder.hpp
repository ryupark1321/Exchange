#include <memory>
#include "engine.hpp"
#include "order.hpp"

class AggregateOrder {
    public:
        std::vector<std::shared_ptr<Order>> match();
        void update();
        void add(std::shared_ptr<Order>);
    private:
        std::vector<std::shared_ptr<Order>> orders_;
        int current_size_;
};