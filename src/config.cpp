#include "config.hpp"

const pcpp::MacAddress Dev::broadcast(BROADCAST);
const pcpp::MacAddress Dev::sendMac(SENDMAC);
const pcpp::MacAddress Dev::recvMac(RECVMAC);
const pcpp::IPv4Address Dev::sendIp(SENDIP);
const pcpp::IPv4Address Dev::recvIp(RECVIP);

void Config::init() {
    std::clog << "config:\n";
    for (auto g : config.groups) {
        std::clog << "\tgroup:" << g->name;
        for (auto s : config.sensors) {
            std::clog << "\n\t\t" << s->name                 //
                      << " : " << s->src.ip << ':' << s->src.port     //
                      << " -> " << s->dst.ip << ':' << s->dst.port  //
                      << " packet:" << s->packetSize;
        }
        std::clog << "\n";
    }
    // 
    new Stat(Dev::dev);
}

void Config::stop() {
    std::clog << "config: stop\n";
    Dev::stop();
    exit(0);
}
