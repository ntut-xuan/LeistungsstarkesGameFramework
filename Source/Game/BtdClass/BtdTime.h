#pragma once

namespace Btd
{
    class BtdTime
    {
        long long _deltatime = 0;
        long long _pastTime = 0;

    public:
        BtdTime();

        void UpdateTime();
    };
}
