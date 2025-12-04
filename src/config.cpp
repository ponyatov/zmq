#include "config.hpp"

void Config::init() {
    std::clog << "config: init\n";
}

void Config::stop() {
    std::clog << "config: stop\n";
    Dev::stop();
    exit(0);
}
