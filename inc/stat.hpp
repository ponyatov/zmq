#pragma once

#include "app.hpp"

class Stat : public Worker {
    static Stat* stat;                           ///< @singleton
    Stat(pcpp::DpdkDevice* dev);                 ///< @ref stat constructor
    pcpp::DpdkDevice::DpdkDeviceStats stats;     ///<
    static const std::chrono::seconds interval;  ///<

   public:
    static void init();
    bool run(uint32_t coreid);
};
