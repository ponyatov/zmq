#include "stat.hpp"

Stat* Stat::stat = nullptr;

const std::chrono::seconds Stat::interval(1);

Stat::Stat(pcpp::DpdkDevice* dev) : Worker(dev) {  //
    std::clog << "stat:\tstart\n";
}

void Stat::init() {
    assert(!stat);
    assert(stat = new Stat(Dev::dev));
}

#define M (1024. * 1024.)
#define G (M * 1024.)

bool Stat::run(uint32_t coreId) {
    assert(Worker::run(coreId));  //
    uint n = 0;
    while (!_stop) {
        dev->getStatistics(stats);

        std::clog << "stat:" << ++n                                       //
                  << " core:" << getCoreId()                              //
                  << " mbuf:" << dev->getAmountOfMbufsInUse()             //
                  << '/' << dev->getAmountOfFreeMbufs()                   //
                  << " packets:" << stats.aggregatedTxStats.packets       //
                  << " pps:" << stats.aggregatedTxStats.packetsPerSec     //
                  << " mbps:" << stats.aggregatedTxStats.bytesPerSec / M  //
                  << " gbit:" << std::setprecision(4)                     //
                  << (stats.aggregatedTxStats.bytesPerSec / G * 8)        //
                  << " mq:" << std::setprecision(4)                       //
                  << (Sender::bytes / G * 8)                              //
                  << "\n";

        Sender::bytes = 0;

        std::this_thread::sleep_for(interval);
    }
    return terminate();
}
