#include "stdafx.h"
#include "BtdTime.h"
#include "CSharp.h"
#include <chrono>

namespace Btd
{
    BtdTime::BtdTime()
    {
        var nowTime = std::chrono::system_clock::to_time_t((std::chrono::system_clock::now()));
        _pastTime = nowTime;
    }

    void BtdTime::UpdateTime()
    {
        var nowTime = std::chrono::system_clock::to_time_t((std::chrono::system_clock::now()));
        _deltatime = nowTime - _pastTime;
        _pastTime = nowTime;
    }
}
