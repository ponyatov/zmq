#pragma once

#include "app.hpp"

class Sender : public Worker {
    static Sender* sender;          ///< singleton
    zmq::socket_t* puller;          ///< mq read socket
    static const uint burst_sz;     ///< `mbuf[size]`
    static zmq::context_t context;  ///<
    Sender(pcpp::DpdkDevice* dev);  ///< singleton constructor
    bool run(uint32_t coreid);      ///< worker run loop

   public:
    static uint bytes;                        ///< stat: sent bytes
    static const std::string zmq;             ///< shared queue
    static void init(pcpp::DpdkDevice* dev);  ///< @ref sender start
};
