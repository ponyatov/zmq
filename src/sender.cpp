#include "app.hpp"

Sender::Sender(pcpp::DpdkDevice* dev, Group* g) : Worker(dev), g(g) {
    zmq = "inproc://" + g->name();
    assert(puller = new zmq::socket_t(Dev::context, zmq::socket_type::pull));
    puller->connect(zmq);
}

bool Sender::run(uint32_t coreId) {
    assert(Worker::run(coreId));
    timespec ts = {0x12345678};            // fake timestamp
    static const uint burst_sz = 64;       // pcpp recommended
    pcpp::MBufRawPacket* burst[burst_sz];  // burst buffer
    pcpp::RawPacket* raw;
    zmq::message_t message;
    while (!_stop) {
        // std::clog << "sender: zmq:" << zmq << "\n";
        // collect
        for (uint idx = 0; idx < burst_sz; idx++) {
            assert(puller->recv(message, zmq::recv_flags::none));
            raw = new pcpp::RawPacket(  //
                (uint8_t*)message.data(), message.size(), ts, true);
            burst[idx] = new pcpp::MBufRawPacket();
            burst[idx]->initFromRawPacket(raw, Dev::dev);
        }
        // burst send
        dev->sendPackets(burst, burst_sz);
    }
    return terminate();
}
