cmake_minimum_required(VERSION 3.0.0)
project(stock_exchange VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wpedantic -O3")

add_executable(
  exchange
  exchange.cpp
  main.cpp
  engine.cpp
  order.cpp
  orderbook.cpp
  stock.cpp
)

target_link_libraries(exchange -lpthread)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
