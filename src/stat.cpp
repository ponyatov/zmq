#include "stat.hpp"

Stat* Stat::stat = nullptr;

Stat::Stat(pcpp::DpdkDevice* dev) : Worker(dev) {
    assert(!Stat::stat);  // check singleton
    Stat::stat = this;
    std::clog << "stat: sheduled\n";
}

#define M (1024. * 1024.)

bool Stat::run(uint32_t coreId) {
    assert(Worker::run(coreId));  //
    while (!_stop) {
        dev->getStatistics(stats);

        std::clog << "stat:"                                              //
                  << " core:" << getCoreId()                              //
                  << " mbuf:" << dev->getAmountOfMbufsInUse()             //
                  << '/' << dev->getAmountOfFreeMbufs()                   //
                  << " packets:" << stats.aggregatedTxStats.packets       //
                  << " pps:" << stats.aggregatedTxStats.packetsPerSec     //
                  << " mbytes:" << stats.aggregatedTxStats.bytes / M      //
                  << " mbps:" << stats.aggregatedTxStats.bytesPerSec / M  //
                  << "\n";

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return terminate();
}
