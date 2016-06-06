#include "json.hpp"
#include "btcmarkets.hpp"

#include <boost/program_options.hpp>

using namespace std;

namespace po = boost::program_options;


bool
parse_options(int acc, const char *avv[], map<string, string>& options);

int main(int acc, const char* avv[])
{
    map<string, string> options;

    if (!parse_options(acc, avv, options))
        return 1;

    bool keys_provided {false};

    unique_ptr<btcm::BtcMarkets> btc_market;

    if (!options["api_key"].empty() && !options["private_key"].empty())
    {
        btc_market = unique_ptr<btcm::BtcMarkets>(
                              new  btcm::BtcMarkets {
                                      options["api_key"],
                                      options["private_key"]
                              });

        keys_provided = true;
    }
    else
    {
        btc_market = unique_ptr<btcm::BtcMarkets>(new  btcm::BtcMarkets);
    }

    btc_market ;

    nlohmann::json j;

    if (!keys_provided)
    {
        // for order_book and tick, api_key and private key are not required
        //j = btc_market->order_book("BTC", "ETH");
        j = btc_market->tick("BTC", "ETH");
    }
    else
    {
        // for these functions, api_key and private key are required
//    j = btc_market.order_history("AUD", "BTC", 10, 1);
//    j = btc_market.trade_history("BTC", "ETH", 2, 10);
//    j = btc_market.open_orders("BTC", "ETH", 2, 10);
//    j = btc_market.create_order("BTC", "ETH", 0.02102020, 0.5, "Bid", "Limit");
//    j = btc_market.create_order("BTC", "ETH", 0.02899998, 1.5, "Ask", "Limit");
//    j = btc_market.cancel_order(102087449);
//    j = btc_market.trades("BTC", "ETH");
//    j = btc_market.order_detail(101549744);
//    j = btc_market.account_balance();
    }

    cout << j.dump() << endl;

    cout << "End of program" << endl;

    return 0;
}


bool
parse_options(int acc, const char *avv[], map<string, string>& options)
{

    options["api_key"]     = {};
    options["private_key"] = {};

    po::options_description desc("btcmarketexamples - example program "
                                 "showcasing using BtcMarkets "
                                 "C++11 RESTful api");

    desc.add_options()
            ("help,h", "produce help message")
            ("api-key,a", po::value<string>(),
             "btcmarkets api key")
            ("private-key,p", po::value<string>(),
             "private key provided by btcmarkets to you")
            ("command,c", po::value<string>()->default_value("tick"),
             "api command to execute: tick, order_book, order_history, trade_history"
                     "open_orders, create_order, cancel_order, trades, "
                     "order_detail, account_balance")
            ("trade-pair,t", po::value<string>()->default_value("BTC/AUD"),
             "instrument/currency pair: BTC/AUD, LTC/AUD, ETH/AUD,"
             "LTC/BTC, ETH/BTC, DAO/BTC, DAO/ETH")
            ("price", po::value<double>(),
             "price when making an order")
            ("volume", po::value<double>(),
             "volume of the order")
            ("side", po::value<string>()->default_value("bid"),
             "side of order: bid, ask")
            ("type", po::value<string>()->default_value("limit"),
             "type of the order: market, limit");

    po::variables_map vm;
    po::store(po::parse_command_line(acc, avv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        cout << desc << endl;
        return false;
    }

    string api_key;
    string private_key;

    if (vm.count("api-key") && vm.count("private-key"))
    {
        options["api_key"]     = vm["api-key"].as<string>();
        options["private_key"] = vm["private-key"].as<string>();
    }

    return true;

}
