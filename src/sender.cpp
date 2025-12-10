#include "app.hpp"

uint Sender::bytes = 0;

Sender::Sender(pcpp::DpdkDevice* dev) : Worker(dev) {
    // assert(puller = new zmq::socket_t(Sender::context,
    // zmq::socket_type::pull)); puller->connect(zmq);
    for (int g = 0; g < maxgroups; g++) {
        puller[g] = nullptr;
        pusher[g] = nullptr;
    }
}

Sender* Sender::sender = nullptr;
zmq::context_t* Sender::context[maxgroups];
// zmq::socket_t* Sender::puller = nullptr;
zmq::socket_t* Sender::puller[maxgroups];
zmq::socket_t* Sender::pusher[maxgroups];
uint8_t Sender::groups = 0;

void Sender::init(pcpp::DpdkDevice* dev) {
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
    //
    while (!_stop) {
        zmq::message_t message;
        for (uint8_t g = 0; g < groups; g++) {
            zmq::recv_result_t res;
            do res = puller[g]->recv(message, zmq::recv_flags::dontwait);
            while (!res);
            Sender::bytes += message.size();
        }
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
#endif  // MQTEST
    }
    // puller->close();
    for (int g = 0; g < groups; g++) {
        pusher[g]->close();
        puller[g]->close();
        context[g]->close();
    }
    return terminate();
}

zmq::socket_t* Sender::connect(Group* g) {
    assert(context[groups] = new zmq::context_t(1));
    //
    assert(puller[groups] = new zmq::socket_t(  //
               *context[groups], zmq::socket_type::pull));
    puller[groups]->connect(transport + g->name());
    //
    assert(pusher[groups] = new zmq::socket_t(  //
               *context[groups], zmq::socket_type::push));
    pusher[groups]->bind(transport + g->name());
    //
    assert(groups++ < maxgroups);
    return pusher[groups - 1];
}
