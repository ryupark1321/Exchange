# Exchange

## Main Components
### Exchange 
  The exchange will simulate the operation of a real stock exchange but in a more limited scope. 
  - Matching Engine
    - Matching engine matches buy orders with sell orders 
    - The currently supported matching algorithms are as follows:
      - FIFO
    - The currently supported order types are as follows: 
      - Instant Order
  - OrderBook
    - Order book keeps track of currently active orders
    - There is one orderbook per each order side (Buy/Sell)
  - Order
    - Orders contain order side, type, expiration date, price, desired stock etc..
  - Stock
    - Stocks contain current price per share and total numbers of shares
  - Investor
    - Investor represents a real investor and contains how much stock this person has

  
