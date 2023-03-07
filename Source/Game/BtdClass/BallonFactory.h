#pragma once

#include <string>
#include <queue>

#include "Ballon.h"

namespace Btd
{
    class BallonFactory
    {
    public:
        static queue<Ballon> BallonPool;
        static vector<Ballon> BallonVector;
        //todo idk should new or not 

        void MakeBallon(string type)
        {
            if (BallonPool.empty())
            {
                Ballon tmpBallon;
                tmpBallon.LoadEmptyBitmap(30, 30);
                tmpBallon.SetTopLeft(10, 10);
                tmpBallon.SetActive(false);
                tmpBallon.SetNowRouteTarget(0);
                tmpBallon.Setspeed(3);
                BallonPool.push(tmpBallon);
            }
            auto next = BallonPool.front();
            next.SetActive(true);
            BallonVector.push_back(next);
        }
    };
}
