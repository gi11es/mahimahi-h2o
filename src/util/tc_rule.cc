/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include <random>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>

#include "child_process.hh"
#include "system_runner.hh"
#include "exception.hh"
#include "socket.hh"

#include "config.h"

using namespace std;

void add_tc_rule( std::string device, uint64_t delay, uint64_t rate, uint64_t loss)
{

    //tc qdisc add dev ingress root netem delay 25ms rate 16000kbit loss 0%
    vector< string > args = { "/sbin/tc", "qdisc", "add", "dev", device, "root", "netem", "delay"};
    if(delay != 0)
    {
        std::ostringstream stringStream;
        stringStream << std::to_string(delay);
        stringStream << "ms";
        args.push_back(stringStream.str());
    }
    else
    {
        std::ostringstream stringStream;
        stringStream << std::to_string(delay);
        args.push_back(stringStream.str());
    }

    args.push_back("rate");
    if(rate != 0)
    {
        std::ostringstream stringStream;
        stringStream << std::to_string(rate);
        stringStream << "kbit";
        args.push_back(stringStream.str());
    }
    else
    {
        std::ostringstream stringStream;
        stringStream << std::to_string(rate);
        args.push_back(stringStream.str());
    }


    args.push_back("loss");
    std::ostringstream stringStream;
    stringStream << std::to_string(loss);
    stringStream << "%";
    args.push_back(stringStream.str());


    for(auto arg : args){
        std::cout << arg << " ";
    }

    run ( args );
}
