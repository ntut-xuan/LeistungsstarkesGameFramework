#pragma once

#include <string>
#include <queue>

#include "Ballon.h"
#include "BlackBallon.h"
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

        static void MakeBallon(BallonType type)
        {
            vector<string> balloonPath = {
                "Resources/bloon/bloon_red.bmp", "Resources/bloon/bloon_blue.bmp", "Resources/bloon/bloon_green.bmp",
                "Resources/bloon/bloon_yellow.bmp"
            };
            if (BallonPool.empty())
            {
                Ballon tmpBallon;
                switch (type)
                {
                case black:
                    tmpBallon.LoadBitmapByString({"Resources/bloon/bloon_black.bmp"}, RGB(0, 0, 0));
                    tmpBallon.SetLayer(0);
                    break;
                default:
                    tmpBallon.LoadBitmapByString(balloonPath, RGB(0, 0, 0));
                    tmpBallon.SetLayer(type);
                    tmpBallon.SetFrameIndexOfBitmap(type);
                    break;
                }
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

        static void handlePopBalloon()
        {
            for (int i = 0; i < static_cast<int>(BallonVector.size()); i++)
            {
                if (BallonVector[i].IsPoped())
                {
                    BallonVector[i].UnshowBitmap();
                    BallonPool.push(BallonVector[i]);
                    BallonVector.erase(BallonVector.begin() + i);
                }
            }
        }
    };
}
