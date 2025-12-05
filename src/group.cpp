#include "app.hpp"

Group::Group(pcpp::DpdkDevice* dev, GROUP* g)
    : Worker(dev),
      g(g)
//   sender(new Sender(dev, this)),
//   pusher(Sender::context, zmq::socket_type::push)
{
    assert(sender = new Sender(dev, this));
    assert(pusher = new zmq::socket_t(Dev::context, zmq::socket_type::push));
    pusher->bind(sender->zmq);
}

bool Group::run(uint32_t coreId) {
    assert(Worker::run(coreId));
    //
    pcpp::Packet packet;
    pcpp::EthLayer eth_layer(Dev::sendMac, Dev::recvMac, PCPP_ETHERTYPE_IP);
    packet.addLayer(&eth_layer);
    pcpp::IPv4Layer ipv4_layer(Dev::sendIp, Dev::recvIp);
    auto ip_hdr = ipv4_layer.getIPv4Header();
    ip_hdr->timeToLive = 5;
    packet.addLayer(&ipv4_layer);
    pcpp::UdpLayer udp_layer(Dev::UDP_PORT, Dev::UDP_PORT);
    packet.addLayer(&udp_layer);
    pcpp::PayloadLayer payload_layer("12345678");
    packet.addLayer(&payload_layer);
    //
    while (!_stop) {
        std::clog << "\ngroup:" << g->name;
        //
        packet.computeCalculateFields();
        // dev->sendPacket(packet);  // debug
        //
        pcpp::RawPacket* raw = packet.getRawPacket();
        std::clog << " size:" << raw->getFrameLength();

        pusher->send(raw->getRawData(), raw->getRawDataLen());
        //
        std::clog << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return terminate();
}
