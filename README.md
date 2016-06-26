# C++ REST API library for BTCMarkets.

[BTCMarkets](https://btcmarkets.net) provides REST [API](https://github.com/BTCMarkets/API)
to their service in number of programming languages, except C++. To
rectify this problem, this library was created.

The library uses header only [json](https://github.com/nlohmann/json) library
and [cpr](https://github.com/whoshuu/cpr) library as a wrapper for libcurl
for making get and post requests to the btcmakrets api service.

For most commands, public `api_key` and secret `private_key` are required 
for authentication for your account. The keys are provided to you by btcmarkets
in your [Account/API key](https://btcmarkets.net/account/apikey) section.

BTCMarkets requires correct timestamps to be added to authentication
requests. This timestamp should be within +/- 30 seconds of their server timestamp.
In Linux this shouldn't be a problem. But just in case, the library has
an option to specify timezone-offset, in seconds, if timestamp adjustments
are required due to differences in your and the server timestamps.

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
  --limit arg (=10)                  number of past orders to fetch
  --since arg (=0)                   from when to fetch the past orders
  --timestamp-offset arg (=0)        offset, in seconds, between your and 
                                     btcmarkerts timestamps
  --order-id arg                     id number of an order to cancel or check 
                                     details
```

### Examples

*Default execution: BTC/AUD tick (no authentication required)*
```bash
./btcmarketsexamples
 
{"bestAsk":811.76,"bestBid":805.16,"currency":"AUD","instrument":"BTC","lastPrice":806.01,"timestamp":1465262979,"volume24h":265.19094}
```

*ETH/BTC tick (no authentication required)*

```bash
./btcmarketsexamples -t ETH/BTC

{"bestAsk":0.02798897,"bestBid":0.02241987,"currency":"BTC","instrument":"ETH","lastPrice":0.02798999,"timestamp":1465263021,"volume24h":182.62025}
```

*DAO/ETH order book (no authentication required)*

```bash
./btcmarketsexamples -t DAO/ETH -c order_book

{"asks":[[0.01,10000.0],[0.01,6334.1398],[0.0101,9938.0659],[0.0102,10000.0],[0.0105,8213.8165],[0.0115,1194.7316],[0.01175,500.0],[0.01199999,1500.0],[0.012,7648.2917],[0.012,1000.0],[0.012,490.2207],[0.0125,100.0],[0.013,9.15],[0.0145,100.0],[0.016345,987.0],[0.0177,600.0],[0.02,244.241],[0.02,1.12839],[0.02,325.8413],[0.051111,500.0],[0.060111,500.0],[0.07,500.0],[0.08299,500.0],[0.1,0.001],[0.101,100.0],[1.0129,99.0]],"bids":[[0.00943102,200.0],[0.00943101,100.0],[0.00943,110.0],[0.00930202,1000.0],[0.00930201,100.0],[0.00913128,1000.0],[0.00906,388.0],[0.009,5000.0],[0.008,4350.0],[0.006,10000.0],[0.005,2000.0],[0.001,0.001]],"currency":"ETH","instrument":"DAO","timestamp":1465263134}
```


*DAO/ETH order book (no authentication required)*

```bash
./btcmarketsexamples -t DAO/ETH -c order_book

{"asks":[[0.01,10000.0],[0.01,6334.1398],[0.0101,9938.0659],[0.0102,10000.0],[0.0105,8213.8165],[0.0115,1194.7316],[0.01175,500.0],[0.01199999,1500.0],[0.012,7648.2917],[0.012,1000.0],[0.012,490.2207],[0.0125,100.0],[0.013,9.15],[0.0145,100.0],[0.016345,987.0],[0.0177,600.0],[0.02,244.241],[0.02,1.12839],[0.02,325.8413],[0.051111,500.0],[0.060111,500.0],[0.07,500.0],[0.08299,500.0],[0.1,0.001],[0.101,100.0],[1.0129,99.0]],"bids":[[0.00943102,200.0],[0.00943101,100.0],[0.00943,110.0],[0.00930202,1000.0],[0.00930201,100.0],[0.00913128,1000.0],[0.00906,388.0],[0.009,5000.0],[0.008,4350.0],[0.006,10000.0],[0.005,2000.0],[0.001,0.001]],"currency":"ETH","instrument":"DAO","timestamp":1465263134}
```


*Recent LTC/AUD trades (no authentication required)*

Only part of the result shown.

```bash
./btcmarketsexamples -t LTC/AUD -c trades

[{"amount":83.627615,"date":1465265085,"price":6.67,"tid":102659907},{"amount":20.0,"date":1465265085,"price":6.68,"tid":102659896},{"amount":0.01485992,"date":1465212487,"price":6.66,"tid":102533229},{"amount":0.01485992,"date":1465212382,"price":6.84,"tid":102533038},{"amount":0.20175051,"date":1465177962,"price":6.66,"tid":102385472},{"amount":5.0,"date":1465039217,"price":7.0,"tid":101896247},{"amount":4.327,"date":1465039027,"price":6.99,"tid":101895354},{"amount":4.327,"date":1465038961,"price":6.6,"tid":101894843},{"amount":2.0,"date":1465038961,"price":6.6,"tid":101894831},{"amount":1.0,"date":1465038961,"price":6.61,"tid":101894820},{"amount":2.673,"date":1465038961,"price":6.71,"tid":101894809},{"amount":14.1,"date":1465029497,"price":7.0,"tid":101871393},{"amount":3.2655605,"date":1465027433,"price":7.0,"tid":101869010},
```

Also can limit number of recent trends, by providing trade id to start from.

```bash
./btcmarketsexamples -c trades -t LTC/AUD --since 101894809

[{"amount":83.627615,"date":1465265085,"price":6.67,"tid":102659907},{"amount":20.0,"date":1465265085,"price":6.68,"tid":102659896},{"amount":0.01485992,"date":1465212487,"price":6.66,"tid":102533229},{"amount":0.01485992,"date":1465212382,"price":6.84,"tid":102533038},{"amount":0.20175051,"date":1465177962,"price":6.66,"tid":102385472},{"amount":5.0,"date":1465039217,"price":7.0,"tid":101896247},{"amount":4.327,"date":1465039027,"price":6.99,"tid":101895354},{"amount":4.327,"date":1465038961,"price":6.6,"tid":101894843},{"amount":2.0,"date":1465038961,"price":6.6,"tid":101894831},{"amount":1.0,"date":1465038961,"price":6.61,"tid":101894820}]
```

*Account balance (authentication required)*

Values in the example output were replaced with dummy values for privacy reasons.

```bash
./btcmarketsexamples -a public_api_key -p secret_private_key -c account_balance

[{"balance":1224253326293,"currency":"AUD","pendingFunds":66969936000},{"balance":0,"currency":"USD","pendingFunds":0},{"balance":7652697853,"currency":"BTC","pendingFunds":1378776555},{"balance":146034433752,"currency":"LTC","pendingFunds":3354855481197},{"balance":943372,"currency":"ETH","pendingFunds":4543243520},{"balance":0,"currency":"FCT","pendingFunds":0},{"balance":0,"currency":"MAID","pendingFunds":0},{"balance":1736535933,"currency":"DAO","pendingFunds":2066000000}]
```

*Create order (authentication required)*

A Bid(default) and Limit (default) order to buy 1 ETH for 18.17 AUD.

```bash
./btcmarketsexamples -a public_api_key -p secret_private_key -c create_order -t ETH/AUD --price 19.17 --volume 1

{"clientRequestId":"1","errorCode":null,"errorMessage":null,"id":102661890,"success":true}
```

An Ask and Limit (default) order to sell 1.5 ETH for 20.01 AUD.

```bash
./btcmarketsexamples -a public_api_key -p secret_private_key -c create_order -t ETH/AUD --price 20.01 --volume 1.5 --side Ask

{"clientRequestId":"1","errorCode":null,"errorMessage":null,"id":102662870,"success":true}
```

An Ask and Market order to sell 10 DAO using ETH.

```bash
./btcmarketsexamples -a public_api_key -p secret_private_key -c create_order -t DAO/ETH --volume 10.0 --side Ask --type Market

{"clientRequestId":"1","errorCode":null,"errorMessage":null,"id":102668298,"success":true}
```

*Cancel order (authentication required)*

```bash
./btcmarketsexamples -a public_api_key -p secret_private_key -c cancel_order --order-id 102662870

{"errorCode":null,"errorMessage":null,"responses":[{"errorCode":null,"errorMessage":null,"id":102662870,"success":true}],"success":true}
```

*Order details (authentication required)*

```bash
./btcmarketsexamples -a public_api_key -p secret_private_key -c order_detail --order-id 102510625

{"errorCode":null,"errorMessage":null,"orders":[{"clientRequestId":null,"creationTime":1465206394338,"currency":"BTC","errorMessage":null,"id":102510625,"instrument":"ETH","openVolume":100000000,"orderSide":"Bid","ordertype":"Limit","price":2241987,"status":"Placed","trades":[],"volume":100000000}],"success":true}
```



*Order history (authentication required)*

Show last two orders of to buy ETH using AUD.

```bash
./btcmarketsexamples -a public_api_key -p secret_private_key -c order_history -t ETH/AUD --limit 2 

{"errorCode":null,"errorMessage":null,"orders":[{"clientRequestId":null,"creationTime":1465287752319,"currency":"AUD","errorMessage":null,"id":102800357,"instrument":"ETH","openVolume":60000000,"orderSide":"Bid","ordertype":"Limit","price":1925000000,"status":"Cancelled","trades":[],"volume":60000000},{"clientRequestId":null,"creationTime":1465287783251,"currency":"AUD","errorMessage":null,"id":102800414,"instrument":"ETH","openVolume":200000000,"orderSide":"Bid","ordertype":"Limit","price":1926000000,"status":"Cancelled","trades":[],"volume":200000000}],"success":true}

```


*Open orders (authentication required)*

Show last open orders of to buy ETH using BTC.

```bash
./btcmarketsexamples -a public_api_key -p secret_private_key -c order_history -t ETH/BTC --limit 1 

{"errorCode":null,"errorMessage":null,"orders":[{"clientRequestId":null,"creationTime":1465289102761,"currency":"BTC","errorMessage":null,"id":102803735,"instrument":"ETH","openVolume":100000000,"orderSide":"Bid","ordertype":"Limit","price":2245882,"status":"Placed","trades":[],"volume":100000000}],"success":true}
```


*Trades history (authentication required)*

Show last trade to buy DAO using ETH.

```bash
./btcmarketsexamples -a public_api_key -p secret_private_key -c trade_history -t DAO/ETH --limit 1 

{"errorCode":null,"errorMessage":null,"success":true,"trades":[{"creationTime":1465266880437,"description":null,"fee":2200000,"id":102669490,"price":1000000,"side":"Bid","volume":1000000000}]}[
```



## How can you help?

Constructive criticism, code and website edits are always good. They can be made through github.

Some Monero are also welcome:
```
48daf1rG3hE1Txapcsxh6WXNe9MLNKtu7W7tKTivtSoVLHErYzvdcpea2nSTgGkz66RFP4GKVAsTV14v6G3oddBTHfxP6tU
```
