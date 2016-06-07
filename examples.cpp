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

    nlohmann::json j;

    if (!keys_provided)
    {
        // for order_book and tick, api_key and private key are not required

        if (options["command"] == "tick")
        {
            j = btc_market->tick(options["currency"],
                                 options["instrument"]);
        }

        if (options["command"] == "order_book")
        {
            j = btc_market->order_book(options["currency"],
                                       options["instrument"]);
        }

        if (options["command"] == "trades")
        {
            j = btc_market->trades(options["currency"],
                                   options["instrument"],
                                   options["since"]); /* since is trade id here */
        }
    }
    else
    {
        // for these functions, api_key and private key are required

        if (options["command"] == "order_history")
        {
            j = btc_market->order_history(options["currency"],
                                          options["instrument"],
                                          stoull(options["limit"]),
                                          stoull(options["since"]));
        }

        if (options["command"] == "trade_history")
        {
            j = btc_market->trade_history(options["currency"],
                                          options["instrument"],
                                          stoull(options["limit"]),
                                          stoull(options["since"]));
        }

        if (options["command"] == "open_orders")
        {
            j = btc_market->open_orders(options["currency"],
                                        options["instrument"],
                                        stoull(options["limit"]),
                                        stoull(options["since"]));
        }

        if (options["command"] == "account_balance")
        {
            j = btc_market->account_balance();
        }

        if (options["command"] == "create_order")
        {
            j = btc_market->create_order(options["currency"],
                                         options["instrument"],
                                         stod(options["price"]),
                                         stod(options["volume"]),
                                         options["side"],
                                         options["type"]);
        }

        if (options["command"] == "cancel_order")
        {
            j = btc_market->cancel_order(stoull(options["order_id"]));
        }


        if (options["command"] == "order_detail")
        {
            j = btc_market->order_detail(stoull(options["order_id"]));
        }

    }

    cout << j << endl;

    return 0;
}



bool
parse_options(int acc, const char *avv[], map<string, string>& options)
{

    options["api_key"]     = {};
    options["private_key"] = {};
    options["command"]     = {};
    options["trade-pair"]  = {};
    options["price"]       = {};
    options["volume"]      = {};
    options["side"]        = {};
    options["order_id"]    = {};
    options["type"]        = {};
    options["limit"]       = {};
    options["since"]       = {};


    set<string> available_commands {"tick", "order_book",
                                    "order_history", "open_orders",
                                    "create_order", "cancel_order",
                                    "trades", "order_detail",
                                    "account_balance", "trade_history"};

    set<string> commands_requiring_auth {"order_history", "open_orders",
                                         "create_order", "cancel_order",
                                         "order_detail", "account_balance",
                                         "trade_history"};

    po::options_description desc("btcmarketexamples - example program "
                                 "showcasing using BtcMarkets "
                                 "C++11 RESTfull API");

    desc.add_options()
            ("help,h", "produce help message")
            ("api-key,a", po::value<string>(),
             "btcmarkets api key")
            ("private-key,p", po::value<string>(),
             "private key provided by btcmarkets to you")
            ("command,c", po::value<string>()->default_value("tick"),
             "api command to execute: tick, order_book, order_history, trade_history, "
                     "open_orders, create_order, cancel_order, trades, "
                     "order_detail, account_balance")
            ("trade-pair,t", po::value<string>()->default_value("BTC/AUD"),
             "instrument/currency pair: BTC/AUD, LTC/AUD, ETH/AUD,"
             "LTC/BTC, ETH/BTC, DAO/BTC, DAO/ETH")
            ("price", po::value<double>(),
             "price when making an order")
            ("volume", po::value<double>(),
             "volume of the order")
            ("side", po::value<string>()->default_value("Bid"),
             "side of order: Bid, Ask")
            ("type", po::value<string>()->default_value("Limit"),
             "type of the order: Market, Limit")
            ("limit", po::value<uint64_t>()->default_value(10),
             "number of past orders to fetch")
            ("since", po::value<uint64_t>()->default_value(0),
             "from when to fetch the past orders.")
            ("order-id", po::value<uint64_t>(),
             "id number of an order to cancel or check details of");

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

    options["command"] = vm["command"].as<string>();

    // check if valid command
    if (available_commands.find(options["command"]) == available_commands.end())
    {
        cerr <<"Command \"" + options["command"] + "\" not recognized! " << endl;
        cout << "Available commands: ";

        stringstream av_commands;

        for (auto& s: available_commands)
            av_commands << s << ", ";

        cout << av_commands.str().erase(av_commands.str().size() - 2) << endl;

        return false;
    }

    options["trade-pair"]  = vm["trade-pair"].as<string>();

    // split trade-pair into instrument and currency
    std::vector<std::string> elems;
    std::stringstream ss(options["trade-pair"]);
    std::string item;
    while (std::getline(ss, item, '/'))
        elems.push_back(item);

    options["instrument"] = elems.at(0);
    options["currency"]   = elems.at(1);

    if (vm.count("price"))
        options["price"]  = std::to_string(vm["price"].as<double>());

    if (vm.count("volume"))
        options["volume"]  = std::to_string(vm["volume"].as<double>());

    if (vm.count("order-id"))
        options["order_id"]  = std::to_string(vm["order-id"].as<uint64_t>());

    options["side"]  = vm["side"].as<string>();
    options["type"]  = vm["type"].as<string>();

    options["limit"]  = std::to_string(vm["limit"].as<uint64_t>());
    options["since"]  = std::to_string(vm["since"].as<uint64_t>());

    if (commands_requiring_auth.find(options["command"]) != commands_requiring_auth.end())
    {
        // check if we have private keys, as they are required for this function
        if (!vm.count("api-key") || !vm.count("private-key"))
        {
            cerr << "api-key and/or private-key are not given!" << endl;
            return false;
        }

        if (options["command"] == "create_order")
        {
            if (!vm.count("price") || !vm.count("volume"))
            {
                cerr << "Cant make an order for " << options["trade-pair"]
                     << ", side: " << options["side"] << ", type: " << options["type"]
                     << ", because price and volume not given!" << endl;
                return false;
            }
        }

        if (options["command"] == "cancel_order")
        {
            if (!vm.count("order-id"))
            {
                cerr << "Cant cancel an order for  "
                     <<  "because order-id not given!" << endl;
                return false;
            }
        }
    }

    return true;

}
