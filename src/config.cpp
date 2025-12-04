#include "config.hpp"

void Config::init() {
    std::clog << "config:\n";
    for (auto g : config.groups) {
        std::clog << "\tgroup:" << g->name;
        for (auto s : config.sensors) {
            std::clog << "\n\t\t" << s->name                        //
                      << " : " << s->src.ip << ':' << s->src.port   //
                      << " -> " << s->dst.ip << ':' << s->dst.port  //
                      << " packet:" << s->packetSize;
        }
        std::clog << "\n";
    }
}

void Config::stop() {
    std::clog << "config: stop\n";
    Dev::stop();
    exit(0);
}
