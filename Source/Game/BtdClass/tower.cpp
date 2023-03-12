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
        int waitDelete = 0;

        for (auto i = throwables.begin(); i != throwables.end(); ++i)
        {
            i->Update();
            if (!i->GetActive())
            {
                waitDelete += 1;
            }
        }
        throwables.erase(throwables.begin(), throwables.begin() + waitDelete);
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

    void Tower::SetShootTimeCounter(float tome)
    {
        shootTimecounter = tome;
    }

    float Tower::GetShootDeltaTime()
    {
        return shootDeltaTime;
    }

    float Tower::GetShootTimeCounter()
    {
        return shootTimecounter;
    }

    void Tower::Update()
    {
        UpdateThrowable();

        if (!BallonFactory::BallonVector.empty() && shootTimecounter > shootDeltaTime)
        {
            Ballon target = focus();
            //todo check in attack range
            Shoot({static_cast<float>(target.GetLeft()), static_cast<float>(target.GetTop())});
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

    void Tower::Shoot(Vector2 target)
    {
        shootTimecounter = 0;
        if (throwablePool.empty() || throwablePool.front().GetActive())
        {
            PushThrowablePool();
        }
        auto next = throwablePool.front();
        Vector2 targetDirection = {
            (target.X - GetLeft()), target.Y - GetTop()
        };
        throwablePool.pop();
        next.SetActive(true);
        next.Init({static_cast<float>(GetLeft()), static_cast<float>(GetTop())});
        next.SetTopLeft(GetLeft(), GetTop());
        next.SetSpeed(5);
        next.SetMaxExistTime(300);
        next.SetMoveDirection(targetDirection.X, targetDirection.Y);
        throwables.push_back(next);
    }

    // it is throwable factory
    void Tower::PushThrowablePool()
    {
        Throwable tmp;
        tmp.LoadBitmapByString({
            throwableName
        });
        throwablePool.push(tmp);
    }
}
