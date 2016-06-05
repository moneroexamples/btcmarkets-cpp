# C++ REST API library for BTCMarkets.

[BTCMarkets](https://btcmarkets.net) provides REST [API](https://github.com/BTCMarkets/API)
to their service in number of programming languages, except C++. To
rectify this problem, this library was created.

The library uses header only [json](https://github.com/nlohmann/json) library
and [cpr](https://github.com/whoshuu/cpr) library as a wraper for libcurl
for making get and post requests to the btcmakrets api service.

## Dependencies Ubuntu 16.04

```bash
```

## Compilation

```bash
git clone --recursive https://github.com/moneroexamples/btcmarkets-cpp.git

cd btcmarkets-cpp && mkdir build && cd build

cmake ..

make
```
