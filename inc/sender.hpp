#pragma once

#include "app.hpp"

class Sender : public Worker {
    static Sender* sender;          ///< singleton
    static const uint burst_sz;     ///< `mbuf[size]`
    Sender(pcpp::DpdkDevice* dev);  ///< singleton constructor
    bool run(uint32_t coreid);      ///< worker run loop

   public:
    static void init(pcpp::DpdkDevice* dev);    ///< @ref sender start
    static const uint8_t maxgroups = 4;         ///<
    static zmq::context_t* context[maxgroups];  ///<
    static zmq::socket_t* puller[maxgroups];    ///< mq read sockets
    static zmq::socket_t* pusher[maxgroups];  ///< ZMQ push sockets /@ref Group/
    static uint8_t groups;                    ///< used @ref pusher s
    static uint bytes;                        ///< stat: sent bytes
    static zmq::socket_t* connect(
        Group*);  ///< connect @ref Group to @ref Sender
    static const std::string transport;
};
