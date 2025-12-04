#pragma once

#include "app.hpp"
#include <zmq.hpp>

class Sender : public Worker {
    Group* g;
    std::string zmq;
    zmq::context_t* context;
    zmq::socket_t* puller;
   public:
    Sender(pcpp::DpdkDevice* dev, Group* g);
    bool run(uint32_t coreid);
};
