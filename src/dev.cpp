#include "app.hpp"

uint8_t Dev::coreNum = 1;
pcpp::CoreMask Dev::coreMask;
pcpp::DpdkDevice *Dev::dev = nullptr;

void Dev::init() {
    std::clog << "dev:init";

    Dev::coreNum = pcpp::getNumOfCores();
    assert(Dev::coreNum >= 4);
    std::clog << " cores:" << (uint)coreNum;

    Dev::coreMask = pcpp::getCoreMaskForAllMachineCores();
    std::clog << " cmask:" << std::format("{:032b}", Dev::coreMask);

    std::clog << " dpdk:";
    assert(pcpp::DpdkDeviceList::initDpdk(Dev::coreMask, Dev::mBufPoolSize));

    std::clog << "ok dev:";
    dev = pcpp::DpdkDeviceList::getInstance().getDeviceByPort(Dev::port);
    std::clog << dev << "\n";
}

void Dev::stop() {
    pcpp::DpdkDeviceList::getInstance().stopDpdkWorkerThreads();
    Dev::dev->close();
}
