#include "stat.hpp"

GARP* GARP::garp = nullptr;

void GARP::init() {
    assert(!garp);
    assert(garp = new GARP(Dev::dev));
}

GARP::GARP(pcpp::DpdkDevice* dev) : Worker(dev) {  //
    std::clog << "garp:\tstart\n";
}

bool GARP::run(uint32_t coreId) {
    assert(Worker::run(coreId));
    pcpp::Packet packet;
    pcpp::EthLayer eth_layer(Dev::sendMac, Dev::recvMac, PCPP_ETHERTYPE_ARP);
    packet.addLayer(&eth_layer);
    pcpp::ArpLayer arp_layer(pcpp::ARP_REQUEST,  //
                             Dev::sendMac, Dev::sendIp, Dev::recvMac,
                             Dev::recvIp);
    packet.addLayer(&arp_layer);
    packet.computeCalculateFields();
    while (!_stop) {
        std::clog << "garp:\n";
        dev->sendPacket(packet);

        std::this_thread::sleep_for(interval);
    }
    return terminate();
}
