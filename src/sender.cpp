#include "app.hpp"

Sender::Sender(pcpp::DpdkDevice* dev, Group* g) : Worker(dev), g(g) {
    zmq = "inproc://" + g->name();
    assert(puller = new zmq::socket_t(Dev::context, zmq::socket_type::pull));
    puller->connect(zmq);
}

bool Sender::run(uint32_t coreId) {
    assert(Worker::run(coreId));  //
    timespec ts = {0x12345678};
    // static const uint buf_sz = 0x2;
    // pcpp::MBufRawPacket* mbuf[buf_sz];
    while (!_stop) {
        // std::clog << "sender: zmq:" << zmq << "\n";
        // collect
        // for (uint idx = 0; idx < buf_sz; idx++) {
        zmq::message_t message;
        assert(puller->recv(message, zmq::recv_flags::none));
        // while (!puller->recv(message, zmq::recv_flags::none)) {
        //     std::clog << ".";
        //     // std::this_thread::sleep_for(std::chrono::milliseconds(111));
        // }
        // std::clog << "\nsender: data[" << message.size();
        pcpp::RawPacket* raw = new pcpp::RawPacket(  //
            (uint8_t*)message.data(), message.size(), ts, true);
        // dev->sendPacket(*raw);
        pcpp::MBufRawPacket* mbuf = new pcpp::MBufRawPacket();
        // mbuf->init();
        mbuf->initFromRawPacket(raw, Dev::dev);
        dev->sendPacket(*mbuf);

        // pcpp::MBufRawPacket* mbuf = new pcpp::MBufRawPacket();
        // mbuf->init(g->dev);
        // // assert(mbuf[idx]->init(g->dev));
        // // mbuf[idx]->setRawData((uint8_t*)message.data(), message.size(),
        // ts);
        // mbuf->setRawData((uint8_t*)message.data(), message.size(), ts);
        // }
        // burst send
        // dev->sendPackets(mbuf, buf_sz);
        //
        // std::clog << "]\n";
        // std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return terminate();
}
