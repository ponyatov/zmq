#include "app.hpp"

uint Sender::bytes = 0;

Sender::Sender(pcpp::DpdkDevice* dev) : Worker(dev) {
    assert(puller = new zmq::socket_t(Dev::context, zmq::socket_type::pull));
    puller->connect(zmq);
}

Sender* Sender::sender = nullptr;
zmq::context_t Sender::context(1);

void Sender::init(pcpp::DpdkDevice* dev) {  //
    assert(!sender);
    assert(sender = new Sender(dev));
}

bool Sender::run(uint32_t coreId) {
    assert(Worker::run(coreId));
#ifndef MQTEST
    timespec ts = {0x12345678};            // fake timestamp
    pcpp::RawPacket* raw;                  //
    pcpp::MBufRawPacket* burst[burst_sz];  // burst buffer
#endif
    zmq::message_t message;
    //
    while (!_stop) {
        auto res = puller->recv(message, zmq::recv_flags::none);
//
#ifndef MQTEST
        // for (uint idx = 0; idx < burst_sz; idx++) {
        raw = new pcpp::RawPacket(  //
            (uint8_t*)message.data(), message.size(), ts, true);
        // collect
        // burst[idx] = new pcpp::MBufRawPacket();
        // burst[idx]->initFromRawPacket(raw, Dev::dev);
        // burst send
        // dev->sendPackets(burst, burst_sz);
        dev->sendPacket(*raw);
        Sender::bytes += raw->getRawDataLen();
#else   // MQTEST
        Sender::bytes += message.size();
#endif  // MQTEST
    }
    return terminate();
}
