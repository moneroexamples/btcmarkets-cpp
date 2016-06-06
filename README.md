# C++ REST API library for BTCMarkets.

[BTCMarkets](https://btcmarkets.net) provides REST [API](https://github.com/BTCMarkets/API)
to their service in number of programming languages, except C++. To
rectify this problem, this library was created.

The library uses header only [json](https://github.com/nlohmann/json) library
and [cpr](https://github.com/whoshuu/cpr) library as a wrapper for libcurl
for making get and post requests to the btcmakrets api service.

## Dependencies 

##### Ubuntu 15.10 and 16.04

```bash
sudo apt install git build-essential cmake libboost-program-options-dev libcurl4-openssl-dev libssl-dev
```


##### Arch Linux

```bash
sudo pacman -Sy git base-devel cmake boost curl
```

## Compilation

```bash
git clone --recursive https://github.com/moneroexamples/btcmarkets-cpp.git

cd btcmarkets-cpp && mkdir build && cd build

cmake ..

make
```

After successful compilation, `btcmarketsexamples` binary should be generated.

## `btcmarketsexamples` options

```bash
btcmarketsexamples - example program showcasing using BtcMarkets C++11 RESTful api:
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
  --side arg (=bid)                  side of order: bid, ask
  --type arg (=limit)                type of the order: market, limit
```

## Examples


