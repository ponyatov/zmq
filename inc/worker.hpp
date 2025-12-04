#pragma once

#include "app.hpp"

class Worker : public pcpp::DpdkWorkerThread {
   protected:
    static std::vector<pcpp::DpdkWorkerThread *> threads;

};
