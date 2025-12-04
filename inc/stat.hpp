#pragma once

#include "app.hpp"

class Stat : public Worker {
    static Stat* stat;
    pcpp::DpdkDevice::DpdkDeviceStats stats;
   public:
    Stat(pcpp::DpdkDevice* dev);
    static void init();
    bool run(uint32_t coreid);
};
