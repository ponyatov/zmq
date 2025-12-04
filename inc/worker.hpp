#pragma once

#include "app.hpp"

class Worker : public pcpp::DpdkWorkerThread {
   protected:
    static std::vector<pcpp::DpdkWorkerThread *> threads;
    pcpp::DpdkDevice *dev;
    bool _stop;
    static uint32_t coreMask;
    uint32_t _coreId;
    static std::atomic<int> active;  ///< active workers count
    bool terminate();

   public:
    Worker(pcpp::DpdkDevice *dev);  ///< worker preinit
    bool run(uint32_t coreid);      ///< run worker
    void stop();                    ///< stop worker (async)
    uint32_t getCoreId() const;     ///< get CPU core bound
    bool schedule();                ///< wait until next send shedule
    static bool any_started;        ///< flag shows any worker was started
};
