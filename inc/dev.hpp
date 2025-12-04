#pragma once

#include "app.hpp"

class Dev {
    /// @name config
    /// @{
    static const uint32_t mBufPoolSize = (0x100000 - 1);
    static const uint16_t MTU = 1400;
    static const uint16_t UDP_PORT = 40000;

    static const pcpp::MacAddress broadcast;
    static const pcpp::MacAddress sendMac;
    static const pcpp::IPv4Address sendIp;
    static const pcpp::MacAddress recvMac;
    static const pcpp::IPv4Address recvIp;

    /// @}

    static uint8_t coreNum;
    static pcpp::CoreMask coreMask;
    static pcpp::DpdkDevice *dev;
    static const uint port = 0;

   public:
    Dev();
    ~Dev();
    static void init();
    static void stop();
};
