#include "app.hpp"

void Dev::init() {
    std::clog << "dev:init";
    Dev::coreNum = pcpp::getNumOfCores();
    assert(Dev::coreNum >= 4);
    std::clog << " cores" << coreNum;

    std::clog << "\n";
}
