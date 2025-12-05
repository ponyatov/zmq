#pragma once

#include "app.hpp"

class Sender : public Worker {
    friend class Group;
    Group* g;
    std::string zmq;
    zmq::socket_t* puller;
   public:
    Sender(pcpp::DpdkDevice* dev, Group* g);
    bool run(uint32_t coreid);
};
