#include "app.hpp"

Group::Group(pcpp::DpdkDevice* dev, GROUP* g) : Worker(dev), g(g) {
    // init order required:
    assert(sender = new Sender(dev, this));
    assert(pusher = new zmq::socket_t(Dev::context, zmq::socket_type::push));
    pusher->bind(sender->zmq);
}

#include "config.json.hpp"

bool Group::run(uint32_t coreId) {
    assert(Worker::run(coreId));
    //
    pcpp::Packet packet;
    pcpp::RawPacket* raw;
    pcpp::EthLayer eth_layer(Dev::sendMac, Dev::recvMac, PCPP_ETHERTYPE_IP);
    packet.addLayer(&eth_layer);
    pcpp::IPv4Layer ipv4_layer(Dev::sendIp, Dev::recvIp);
    auto ip_hdr = ipv4_layer.getIPv4Header();
    ip_hdr->timeToLive = 5;
    packet.addLayer(&ipv4_layer);
    pcpp::UdpLayer udp_layer(Dev::UDP_PORT, Dev::UDP_PORT);
    packet.addLayer(&udp_layer);
    pcpp::PayloadLayer payload_layer(S_1_1.start, S_1_1.packetSize);
    packet.addLayer(&payload_layer);
    //
    uint8_t split_ = 0;
    const uint8_t split = 8;
    auto udp_hdr = udp_layer.getUdpHeader();
    //
    while (!_stop) {
        // std::clog << "\ngroup:" << g->name;
        //
        udp_hdr->portDst = htobe16(Dev::UDP_PORT + ((++split_) % split));
        packet.computeCalculateFields();
        //
        raw = packet.getRawPacket();
        // pusher->send(zmq::buffer(raw->getRawData(), raw->getRawDataLen()));
        // pusher->send(zmq::buffer(S_1_1.start, S_1_1.size));
        pusher->send(zmq::buffer(S_1_1.start, 18500 * 28));
        //
        // std::clog << "\n";
        // std::this_thread::sleep_for(interval);
    }
    return terminate();
}
