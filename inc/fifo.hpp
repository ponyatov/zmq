#pragma once

#include <zmq.hpp>

#include "app.hpp"

class FIFO {
    zmq::context_t* context;
    zmq::socket_t* push_socket;
    zmq::socket_t* pull_socket;

   public:
    FIFO(std::string name);
};
