#pragma once

#include "app.hpp"

/// @brief @ref SENSOR s group (single send with grouped packets)
struct GROUP {
    std::string name;              ///<
    uint duration;                 ///<
    bool loop;                     ///< repeat sending
    uint freq;                     ///<
    std::vector<SENSOR*> sensors;  ///<
    //     uint packetSize;               ///< UDP payload size, bytes
};

class Sender;

class Group : public Worker {
    GROUP* g;               ///< @ref GROUP configuration
    Sender* sender;         ///< DPDK sender for every Group
    zmq::socket_t* pusher;  ///< ZMQ push socket

   public:
    Group(pcpp::DpdkDevice* dev, GROUP* g);
    bool run(uint32_t coreid);
    std::string name() const { return g->name; }
};
