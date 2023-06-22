#include "exchange.hpp"
#include <iostream>

// Should support test mode or just regular functioning mode 
int main(int argc, char* argv[]) {
  // Initialize Things 
  Exchange& exchange = Exchange::getInstance();
  exchange.update();
  std::cout << argc << std::endl;  
}