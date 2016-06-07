# C++ REST API library for BTCMarkets.

[BTCMarkets](https://btcmarkets.net) provides REST [API](https://github.com/BTCMarkets/API)
to their service in number of programming languages, except C++. To
rectify this problem, this library was created.

The library uses header only [json](https://github.com/nlohmann/json) library
and [cpr](https://github.com/whoshuu/cpr) library as a wrapper for libcurl
for making get and post requests to the btcmakrets api service.

### Dependencies 

##### Ubuntu 15.10 and 16.04

```bash
sudo apt install git build-essential cmake libboost-program-options-dev libcurl4-openssl-dev libssl-dev
```


##### Arch Linux

```bash
sudo pacman -Sy git base-devel cmake boost curl openssl
```

### Compilation

```bash
git clone --recursive https://github.com/moneroexamples/btcmarkets-cpp.git

cd btcmarkets-cpp && mkdir build && cd build

cmake ..

make
```

After successful compilation, `btcmarketsexamples` binary should be generated.

### `btcmarketsexamples` options

```bash
btcmarketexamples - example program showcasing using BtcMarkets C++11 RESTfull API:
  -h [ --help ]                      produce help message
  -a [ --api-key ] arg               btcmarkets api key
  -p [ --private-key ] arg           private key provided by btcmarkets to you
  -c [ --command ] arg (=tick)       api command to execute: tick, order_book, 
                                     order_history, trade_history, open_orders,
                                     create_order, cancel_order, trades, 
                                     order_detail, account_balance
  -t [ --trade-pair ] arg (=BTC/AUD) instrument/currency pair: BTC/AUD, 
                                     LTC/AUD, ETH/AUD,LTC/BTC, ETH/BTC, 
                                     DAO/BTC, DAO/ETH
  --price arg                        price when making an order
  --volume arg                       volume of the order
  --side arg (=Bid)                  side of order: Bid, Ask
  --type arg (=Limit)                type of the order: Market, Limit
  --order-id arg                     id number of an order to cancel or check 
                                     details of
```

### Examples

**Default execution: BTC/AUD tick (no authentication required)**
```bash
./btcmarketsexamples
 
{"bestAsk":811.76,"bestBid":805.16,"currency":"AUD","instrument":"BTC","lastPrice":806.01,"timestamp":1465262979,"volume24h":265.19094}
```

**ETH/BTC tick (no authentication required)**

```bash
./btcmarketsexamples -t ETH/BTC

{"bestAsk":0.02798897,"bestBid":0.02241987,"currency":"BTC","instrument":"ETH","lastPrice":0.02798999,"timestamp":1465263021,"volume24h":182.62025}
```

**DAO/ETH order book (no authentication required)**

```bash
./btcmarketsexamples -t DAO/ETH -c order_book

/btcmarketsexamples -t DAO/ETH -c order_book
{"asks":[[0.01,10000.0],[0.01,6334.1398],[0.0101,9938.0659],[0.0102,10000.0],[0.0105,8213.8165],[0.0115,1194.7316],[0.01175,500.0],[0.01199999,1500.0],[0.012,7648.2917],[0.012,1000.0],[0.012,490.2207],[0.0125,100.0],[0.013,9.15],[0.0145,100.0],[0.016345,987.0],[0.0177,600.0],[0.02,244.241],[0.02,1.12839],[0.02,325.8413],[0.051111,500.0],[0.060111,500.0],[0.07,500.0],[0.08299,500.0],[0.1,0.001],[0.101,100.0],[1.0129,99.0]],"bids":[[0.00943102,200.0],[0.00943101,100.0],[0.00943,110.0],[0.00930202,1000.0],[0.00930201,100.0],[0.00913128,1000.0],[0.00906,388.0],[0.009,5000.0],[0.008,4350.0],[0.006,10000.0],[0.005,2000.0],[0.001,0.001]],"currency":"ETH","instrument":"DAO","timestamp":1465263134}
```