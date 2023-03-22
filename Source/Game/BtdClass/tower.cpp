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
        shootTimecounter = 0;
    }

    bool Tower::IsMovable()
    {
        return _isMovable;
    }

    void Tower::SetIsMove(bool move)
    {
        _isMovable = move;
    }

    int Tower::GetRange()
    {
        return _range;
    }

    void Tower::UpdateThrowable()
    {
        int waitDelete = 0;

        for (int i=0; i<(int)throwables.size(); i++)
        {
            throwables[i]->Update();
            if (!throwables[i]->GetActive())
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
            if (Vector2Distance(GetCenter(), b.GetCenter()) <
                Vector2Distance(GetCenter(), target.GetCenter()))
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
        if (_isActive)
        {
            UpdateThrowable();

            if (!BallonFactory::BallonVector.empty() && shootTimecounter > shootDeltaTime)
            {
                Ballon target = focus();
                if (Vector2Distance(GetCenter(), target.GetCenter()) < (float)_range)
                {
                    Shoot({static_cast<float>(target.GetLeft()), static_cast<float>(target.GetTop())});
                }
            }
            else
            {
                shootTimecounter += delayCount / 100.F;
            }
        }
    }

    void Tower::SetShootDeltaTime(float time)
    {
        shootDeltaTime = time;
    }

    void Tower::Shoot(Vector2 target)
    {
        shootTimecounter = 0;
        if (throwablePool.empty() || throwablePool.front()->GetActive())
        {
            PushThrowablePool();
        }
        auto next = move(throwablePool.front());
        Vector2 targetDirection = {
            (target.X - GetLeft()), target.Y - GetTop()
        };
        throwablePool.pop();
        next->SetActive(true);
        next->InitByCenter(GetCenter());
        next->SetSpeed(5);
        next->SetMaxExistTime(300);
        next->SetMoveDirection(targetDirection.X, targetDirection.Y);
        throwables.push_back(std::move(next));
    }

    void Tower::SetThrowablePath(vector<string> name)
    {
        ThrowablePath = name;
    }

    // it is throwable factory
    void Tower::PushThrowablePool()
    {
        unique_ptr<Throwable> tmp = make_unique<Throwable>(Throwable());
        tmp->LoadBitmapByString({"resources/towers/bomb/bomb.bmp"}
                               ,RGB(255, 255, 255));
        throwablePool.push(std::move(tmp));
    }
}
