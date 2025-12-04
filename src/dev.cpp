#include "app.hpp"

uint8_t Dev::coreNum = 1;
pcpp::CoreMask Dev::coreMask;
pcpp::DpdkDevice *Dev::dev = nullptr;
uint16_t Dev::MTU = 1500;

void Dev::init() {
    std::clog << "dev:";

    Dev::coreNum = pcpp::getNumOfCores();
    assert(Dev::coreNum >= 4);
    std::clog << " cores:" << (uint)coreNum;

    Dev::coreMask = pcpp::getCoreMaskForAllMachineCores();
    std::clog << " cmask:" << std::format("{:032b}", Dev::coreMask) << "\n";

    assert(pcpp::DpdkDeviceList::initDpdk(Dev::coreMask, Dev::mBufPoolSize));

    // std::clog << " port:" << Dev::port;
    dev = pcpp::DpdkDeviceList::getInstance().getDeviceByPort(Dev::port);
    Dev::MTU = dev->getMtu();
    std::clog << "dev: " << dev->getDeviceName()            //
              << " id:" << dev->getDeviceId()               //
              << "\n\tmac:" << dev->getMacAddress()         //
              << " pci:" << dev->getPciAddress()            //
              << " pmd:" << dev->getPMDName()               //
              << "\n\ttx:" << dev->getTotalNumOfTxQueues()  //
              << " rx:" << dev->getTotalNumOfRxQueues()     //
              << " mbuf:" << dev->getAmountOfMbufsInUse()   //
              << '/' << dev->getAmountOfFreeMbufs()         //
              << " mtu:" << dev->getMtu()                   //
              << "\n";
    assert(dev->open());
}

void Dev::stop() {
    pcpp::DpdkDeviceList::getInstance().stopDpdkWorkerThreads();
    Dev::dev->close();
}
