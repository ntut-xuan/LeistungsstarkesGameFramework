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

        static void MakeBallon(Layer::NormalBallonLayer type)
        {
            Vector2 startPosition = Map::GetStartPosition();
            MakeBallonByPosition(type, startPosition, 0);
        }

        static void MakeBallonByPosition(Layer::NormalBallonLayer type, Vector2 startPosition, int nowRouteTarget)
        {
            vector<string> balloonPath = {
                "Resources/bloon/bloon_red.bmp", "Resources/bloon/bloon_blue.bmp", "Resources/bloon/bloon_green.bmp",
                "Resources/bloon/bloon_yellow.bmp", "Resources/bloon/bloon_black.bmp"
            };
            if (BallonPool.empty())
            {
                Ballon tmpBallon;
                tmpBallon.LoadBitmapByString(balloonPath, RGB(0, 0, 0));
                tmpBallon.SetLayer(0);
                tmpBallon.SetFrameIndexOfBitmap(0);
                tmpBallon.SetTopLeft(static_cast<int>(startPosition.X), static_cast<int>(startPosition.Y));
                tmpBallon.SetActive(false);
                tmpBallon.SetNowRouteTarget(0);
                tmpBallon.Setspeed(3);
                BallonPool.push(tmpBallon);
            }
            auto next = BallonPool.front();
            switch (type)
            {
            case Layer::black:
                // next.LoadBitmapByString({"Resources/bloon/bloon_black.bmp"}, RGB(0, 0, 0));
                next.SetFrameIndexOfBitmap(Layer::black);
                next.SetLayer(0);
                next.Setspeed(3);
                next.SetType(BallonType::black);
                break;
            default:
                next.LoadBitmapByString(balloonPath, RGB(0, 0, 0));
                next.SetLayer(type);
                next.SetFrameIndexOfBitmap(type);
                next.Setspeed(3);
                next.SetType(BallonType::normal);
                break;
            }
            next.SetNowRouteTarget(nowRouteTarget);
            next.SetTopLeft(static_cast<int>(startPosition.X), static_cast<int>(startPosition.Y));
            next.SetIsPoped(false);
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
                Ballon b = BallonVector[i];
                if (BallonVector[i].IsPoped())
                {
                    BallonType::BallonType type = BallonVector[i].GetType();
                    if (type == BallonType::black || type == BallonType::white)
                    {
                        int nowRouteTarget = BallonVector[i].GetNowRouteTarget();
                        Vector2 position = {
                            static_cast<float>(BallonVector[i].GetLeft()), static_cast<float>(BallonVector[i].GetTop())
                        };
                        MakeBallonByPosition(Layer::yelllow, position, nowRouteTarget);
                        MakeBallonByPosition(Layer::yelllow, position, nowRouteTarget);
                    }
                    BallonPool.push(BallonVector[i]);
                    BallonVector.erase(BallonVector.begin() + i);
                }
            }
        }
    };
}
