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

    btcm::BtcMarkets btc_market {options["api_key"],
                                 options["private_key"]};

    nlohmann::json j;

//    j = btc_market.order_history("AUD", "BTC", 10, 1);
//    j = btc_market.trade_history("BTC", "ETH", 2, 10);
//    j = btc_market.open_orders("BTC", "ETH", 2, 10);
//    j = btc_market.create_order("BTC", "ETH", 0.02102020, 0.5, "Bid", "Limit");
//    j = btc_market.create_order("BTC", "ETH", 0.02899998, 1.5, "Ask", "Limit");
//    j = btc_market.cancel_order(102087449);
    j = btc_market.order_book("AUD", "BTC");
//    j = btc_market.tick("BTC", "ETH");
//    j = btc_market.trades("BTC", "ETH");
//    j = btc_market.order_detail(101549744);
//    j = btc_market.account_balance();

    cout << j.dump() << endl;


    cout << "End of program" << endl;

    return 0;
}


bool
parse_options(int acc, const char *avv[], map<string, string>& options)
{
    po::options_description desc("btcmarketsmain - rest api test");

    desc.add_options()
            ("help,h", "produce help message")
            ("api-key,a", po::value<string>(),
             "btcmarkets api key")
            ("private-key,p", po::value<string>(),
             "private key provided by btcmarkets to you");

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
    else
    {
        cerr << "api-key and/or private key not provided!." << endl;
        return false;
    }

    return true;

}
