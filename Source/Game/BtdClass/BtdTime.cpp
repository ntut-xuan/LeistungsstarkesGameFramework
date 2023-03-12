#include "stdafx.h"
#include "BtdTime.h"
#include "CSharp.h"

namespace Btd
{
    BtdTime::BtdTime()
    {
        var nowTime = std::chrono::system_clock::to_time_t((std::chrono::system_clock::now()));
        _pastTime = nowTime;
    }

}
