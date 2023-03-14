#pragma once

#include <string>
#include <queue>

#include "Ballon.h"
#include "map.h"
#include "TowerFactory.h"

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
                tmpBallon.LoadBitmapByString({"Resources/bloon/bloon_red.bmp"},RGB(0, 0, 0));
                Vector2 startPosition = Map::GetStartPosition();
                tmpBallon.SetTopLeft(static_cast<int>(startPosition.X), static_cast<int>(startPosition.Y));
                tmpBallon.SetActive(false);
                tmpBallon.SetNowRouteTarget(0);
                tmpBallon.Setspeed(3);
                BallonPool.push(tmpBallon);
            }
            auto next = BallonPool.front();
            BallonPool.pop();
            next.SetActive(true);
            BallonVector.push_back(next);
        }

        static void UpdateBloon()
        {
            for (Ballon& b : BallonVector)
            {
                b.Update();
            }
        }

        static void handlePopBalloon ()
        {
            for (int i=0; i<(int)BallonVector.size(); i++)
            {
                bool b = BallonVector[i].IsPoped();
                if (b == true)
                {
                    BallonVector[i].UnshowBitmap();
                    BallonVector.erase(BallonVector.begin()+i);
                }
            }
        }
    };
}
