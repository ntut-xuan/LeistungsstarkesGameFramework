#pragma once
#include <queue>

#include "Ballon.h"
#include "Map.h"


namespace Btd
{
    class BallonFactory
    {
    public:
        static queue<Ballon> BallonPool;
        static vector<Ballon> BallonVector;

        static vector<UnitRound> BallonRound;
        static int BallonCounter;
        static int BallonTimer;

        static void SetNextRound(vector<UnitRound> rounds)
        {
            BallonRound = rounds;
            BallonCounter = 0;
            BallonTimer = 0;
        }

        static bool UpdateRound(int DeltaTime)
        {
            if (BallonTimer <= 0)
            {
                if (BallonCounter >= static_cast<int>(BallonRound.size()))
                {
                    return true;
                }
                MakeBallon(BallonRound[BallonCounter].type);
                BallonTimer = BallonRound[BallonCounter].nextTime;
                BallonCounter ++;
            }
            else
            {
                BallonTimer -= DeltaTime;
            }
            return false;
        }

        static void MakeBallon(BallonType type)
        {
            vector<string> balloonPath = {
                "Resources/bloon/bloon_red.bmp", "Resources/bloon/bloon_blue.bmp", "Resources/bloon/bloon_green.bmp",
                "Resources/bloon/bloon_yellow.bmp"
            };
            Vector2 startPosition = Map::GetStartPosition();
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
                tmpBallon.SetActive(false);
                BallonPool.push(tmpBallon);
            }
            auto next = BallonPool.front();
            BallonPool.pop();
            next.SetActive(true);
            next.SetTopLeft(static_cast<int>(startPosition.X), static_cast<int>(startPosition.Y));
            next.SetNowRouteTarget(0);
            next.SetIsPoped(false);
            next.Setspeed(3);
            next.SetLayer(type);
            BallonVector.push_back(next);
        }

        static void UpdateBloon()
        {
            for (Ballon& b : BallonVector)
            {
                b.Update();
            }
            handlePopBalloon();
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
