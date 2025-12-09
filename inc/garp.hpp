#pragma once

#include "app.hpp"

/// worker: regular sending Gratuitous ARP annonsments
/// @ingroup worker
class GARP : public Worker {
    static GARP* garp;
    static const std::chrono::seconds interval;

    GARP(pcpp::DpdkDevice* dev);
    bool run(uint32_t coreid);

   public:
    static void init();
};
