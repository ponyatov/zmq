#pragma once

#include "app.hpp"

class GARP : public Worker {
    static GARP* garp;
    static const std::chrono::seconds interval;

   public:
    GARP(pcpp::DpdkDevice* dev);
    static void init();
    bool run(uint32_t coreid);
};
