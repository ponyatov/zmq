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

class Group : public Worker {
   public:
    Group();
};
