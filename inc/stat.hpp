#pragma once

#include "app.hpp"

class Stat : public Worker {
   public:
    Stat(pcpp::DpdkDevice *dev) : Worker(dev) {}
};
