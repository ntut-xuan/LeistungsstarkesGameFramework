#pragma once

#include "CSharp.h"
#include <chrono>
namespace Btd
{
    class BtdTime
    {
        static long long _deltaTime ;
        static long long _pastTime ;

    public:
        BtdTime();

        static void UpdateTime()
        {
            var nowTime = std::chrono::system_clock::to_time_t((std::chrono::system_clock::now()));
            _deltaTime = nowTime - _pastTime;
            _pastTime = nowTime;
        }
    };
    long long BtdTime::_deltaTime = 0;
    long long BtdTime::_pastTime = 0;
}
