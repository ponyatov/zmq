#pragma once

#include "app.hpp"

class Dev {
    static const uint32_t mBufPoolSize = (0x100000 - 1);
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
