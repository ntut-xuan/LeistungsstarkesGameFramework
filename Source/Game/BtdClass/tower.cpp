#include "stdafx.h"
#include "BallonFactory.h"
#include "BtdUtil.h"
#include "map.h"
#include "Tower.h"

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

    void Tower::SetIsMove(bool move)
    {
        _isMovable = move;
    }

    void Tower::UpdateThrowable()
    {
        for (auto i = throwables.begin(); i != throwables.end(); ++i)
        {
            i->Update();
            if (!i->GetActive())
            {
                throwables.erase(i, i++);
            }
        }
    }

    Ballon Tower::focus()
    {
        Ballon target;

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

        return target;
    }

    void Tower::Update()
    {
        UpdateThrowable();

        if (!BallonFactory::BallonVector.empty() && shootTimecounter > shootDeltaTime)
        {
            Ballon target = focus();
            //todo check in attack range
            Shoot(target);
        }
        else
        {
            shootTimecounter += delayCount / 100.F;
        }
    }

    void Tower::SetShootDeltaTime(float time)
    {
        shootDeltaTime = time;
    }

    //todo set throwable target position
    void Tower::Shoot(Ballon target)
    {
        shootTimecounter = 0;
        if (throwablePool.empty() || throwablePool.front().GetActive())
        {
            PushThrowablePool();
        }
        auto next = throwablePool.front();
        Vector2 targetDirection = {
            static_cast<float>(target.GetLeft() - GetLeft()), static_cast<float>(target.GetTop()) - GetTop()
        };
        throwablePool.pop();
        next.SetActive(true);
        next.SetTopLeft(static_cast<int>(GetLeft()), static_cast<int>(GetTop()));
        next.SetMoveDirection(targetDirection.X, targetDirection.Y);
        throwables.push_back(next);
    }

    // it is throwable factory
    void Tower::PushThrowablePool()
    {
        //var throwable = MakeThrowable();
        //throwable.SetActive(active);
        Throwable tmp;
        tmp.LoadBitmapByString({
            "resources/bomb.bmp"
        });
        tmp.SetActive(true);
        tmp.SetTopLeft(GetLeft(), GetTop());
        tmp.SetSpeed(5);
        tmp.SetMoveDirection(10, 10);
        throwablePool.push(tmp);
    }

    void Tower::MakeThrowable()
    {
        // return throwableFactory.MakeThrowable(throwableName);
    }
}
