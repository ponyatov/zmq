#include "config.hpp"

const pcpp::MacAddress Dev::broadcast(BROADCAST);
const pcpp::MacAddress Dev::sendMac(SENDMAC);
const pcpp::MacAddress Dev::recvMac(RECVMAC);
const pcpp::IPv4Address Dev::sendIp(SENDIP);
const pcpp::IPv4Address Dev::recvIp(RECVIP);

void Config::init() {
    std::clog << "config: init\n";
}

void Config::stop() {
    std::clog << "config: stop\n";
    Dev::stop();
    exit(0);
}
