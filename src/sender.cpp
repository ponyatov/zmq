#include "app.hpp"

Sender::Sender(pcpp::DpdkDevice* dev, Group* g) : Worker(dev), g(g) {
    zmq = "inproc://" + g->g->name;
    assert(context = new zmq::context_t());
    puller = new zmq::socket_t(context,zmq::socket_type::pull);
}

bool Sender::run(uint32_t coreId) {
    assert(Worker::run(coreId));  //
    while (!_stop) {
        std::clog << "sender: zmq:" << zmq;
        std::clog << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return terminate();
}
