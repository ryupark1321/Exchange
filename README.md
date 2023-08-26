# Exchange

## Main Components
### Exchange 
  The exchange will simulate the operation of a real stock exchange but in a more limited scope. 

  Client - Server Model
  # Server - Exchange
  - Should send update information to clients
  - Should receive/process orders from clients
    - needs access to orderbooks and collection of stocks available on the market
  ## OrderBook
  - Should contain a collection of aggregate orders
  - Should keep buy and sell sides separately
  - Should have matching engine built into it
  - Needs a toJson function
  ## Aggregate Order
  - Mutual exclusion on update/add
  - Should have matching engine built into it
  - Data Structure Architecture
    - Index <=> Time Rank O(1)
    - Real Ordering <=> Pro Rata? O(1)
    - Should have easy removal from none of the endpoints
    - Should have easy removal 

  ## Engine
  - Is an interface with two virtual functions fifo() and match()
  - Should act on OrderBooks

  ## Order
  - Order contains price/quantity/side/type/time

  ## Stock
  - Stock contains the maximum number of shares, name, abbreviation, current price

  # Client - Customer
  - Should send/receive exchange info to server

  ## Investor
  - Should contain a collection of stocks that the investor owns
  
