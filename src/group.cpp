#include "app.hpp"

Group::Group(pcpp::DpdkDevice* dev, GROUP* g) : Worker(dev), g(g) {
    std::clog << "\n" << g->name;
    sender = new Sender(dev, this);  // start sender for every Group
}

bool Group::run(uint32_t coreId) {
    assert(Worker::run(coreId));  //
    while (!_stop) {
        std::clog << "group:" << g->name;
        std::clog << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return terminate();
}
