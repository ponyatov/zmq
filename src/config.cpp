#include "config.hpp"

const std::chrono::seconds GARP::interval(15);

// const std::string Sender::zmq = "inproc://sender";
// 30 gbit single sockets only!
// const std::string Sender::zmq = "ipc://tmp/sender";
// 1 group: 21 gbit
// 2 group: 20 gbit
// 3 group: 21 gbit
// 4 group: 20 gbit
//
// const std::string Sender::transport = "inproc://";
// 1 group: 25 gbit
// 2 group: 23 gbit
// 3 group: 0.5..31 gbit (болтанка)
// 4 group: 3..19 gbit (болтанка)
const std::string Sender::transport = "ipc://tmp/";
// 1 group: 23 gbit
// 2 group: 15 gbit
// 3 group: 15 gbit
// 4 group: 12..16 gbit
const uint Sender::burst_sz = 64;

const pcpp::MacAddress Dev::broadcast(BROADCAST);
const pcpp::MacAddress Dev::sendMac(SENDMAC);
const pcpp::MacAddress Dev::recvMac(RECVMAC);
const pcpp::IPv4Address Dev::sendIp(SENDIP);
const pcpp::IPv4Address Dev::recvIp(RECVIP);

void Config::init() {
    std::clog << "config:\n";
    Sender::init(Dev::dev);
    for (auto g : config.groups) new Group(Dev::dev, g);
}

void Config::stop() {
    std::clog << "config: stop\n";
    Dev::stop();
    exit(0);
}
