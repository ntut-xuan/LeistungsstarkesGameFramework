#include "stdafx.h"
#include "BallonFactory.h"
#include "BtdUtil.h"
#include "map.h"
#include "tower.h"

namespace Btd
{
    Tower::Tower()
    {
        _isUpgrade[0] = false;
        _isUpgrade[1] = false;
        _isMovable = true;
    }

    bool Tower::IsMovable()
    {
        return _isMovable;
    }

    void Tower::SetNotMove()
    {
        _isMovable = false;
    }

    void Tower::Update()
    {
        for (auto &t : throwables)
        {
            t.Update();
        }
        Ballon target;
        if (BallonFactory::BallonVector.size() != 0)
        {
            target = BallonFactory::BallonVector[0];
            for (Ballon b : BallonFactory::BallonVector)
            {
                if ((b.GetNowRouteTarget() > target.GetNowRouteTarget()) ||
                    (b.GetNowRouteTarget() == target.GetNowRouteTarget() &&
                        Vector2Distance({static_cast<float>(b.GetLeft()), static_cast<float>(b.GetTop())},
                                        Map::GetRoute()[b.GetNowRouteTarget()]) <
                        Vector2Distance({static_cast<float>(target.GetLeft()), static_cast<float>(target.GetTop())},
                                        Map::GetRoute()[b.GetNowRouteTarget()])))
                {
                    target = b;
                }
            }
            //todo check in attack range
            Shoot();
        }
    }


    //todo set throwable target position
    void Tower::Shoot()
    {
        if (throwablePool.empty() || throwablePool.front().GetActive())
        {
            PushThrowablePool(true);
        }
        else
        {
            auto next = throwablePool.front();
            throwablePool.pop();
            next.SetActive(true);
            next.SetTopLeft(static_cast<int>(throwLocal.X), static_cast<int>(throwLocal.Y));
            throwablePool.push(next);
        }
    }

    //todo when push can set top left
    void Tower::PushThrowablePool(bool active)
    {
        //var throwable = MakeThrowable();
        //throwable.SetActive(active);
        Throwable tmp;
        tmp.LoadEmptyBitmap(100, 100);
        tmp.SetActive(true);
        tmp.SetTopLeft(GetLeft(), GetTop());
        tmp.SetSpeed(5);
        tmp.SetMoveDirection(10, 10);
        throwables.push_back(tmp);
    }

    void Tower::MakeThrowable()
    {
        // return throwableFactory.MakeThrowable(throwableName);
    }
}
