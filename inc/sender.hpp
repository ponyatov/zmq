#pragma once

#include "app.hpp"

class Sender : public Worker {
    friend class Group;
    friend class Stat;
    static Sender* sender;         ///< singleton
    static const std::string zmq;  ///<
    zmq::socket_t* puller;         ///<
    static const uint burst_sz;    ///< `mbuf[size]`
    static uint bytes;

   public:
    Sender(pcpp::DpdkDevice* dev);
    bool run(uint32_t coreid);
    static void init(pcpp::DpdkDevice* dev);
};
