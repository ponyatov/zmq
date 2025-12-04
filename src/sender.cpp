#include "app.hpp"

Sender::Sender(pcpp::DpdkDevice* dev, Group* g) : Worker(dev), g(g) {
    zmq = "inproc://" + g->name();
    assert(puller = new zmq::socket_t(Sender::context, zmq::socket_type::pull));
    puller->connect(zmq);
}

bool Sender::run(uint32_t coreId) {
    assert(Worker::run(coreId));  //
    timespec ts = {0x12345678};
    static const uint buf_sz = 0x2;
    pcpp::MBufRawPacket* mbuf[buf_sz];
    while (!_stop) {
        std::clog << "sender: zmq:" << zmq;
        std::clog << "\n";
        // collect
        for (uint idx = 0; idx < buf_sz; idx++) {
            zmq::message_t message;
            while(!puller->recv(message,zmq::recv_flags::none)) {
                std::clog << "\tpuller:wait";
                std::this_thread::sleep_for(std::chrono::milliseconds(111));
            }
            std::clog << "\tpuller:data[\n" << message.size() << "]\n";
            assert(mbuf[idx]->init(g->dev));
            mbuf[idx]->setRawData((uint8_t*)message.data(), message.size(), ts);
        }
        // burst send
        dev->sendPackets(mbuf, buf_sz);
        //
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return terminate();
}

zmq::context_t Sender::context(1);
