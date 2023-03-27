#include "stdafx.h"
#include "BloonFactory.h"
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
        ThrowablePath = {"resources/towers/bomb/bomb.bmp"};
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
        for (int i=(int)throwables.size()-1; i>=0; i--)
        {
            throwables[i]->Update();
            if (Vector2Distance(throwables[i]->GetCenter(), GetCenter()) > (float)_range + 70) 
            {
                // if throwable fly over (range + 70) distance will be erase
                throwables[i]->SetActive(false);
            }
            if (!throwables[i]->GetActive())
            {
                throwables.erase(throwables.begin() + i);
            }
        }
    }

    Bloon Tower::focus()
    {
        Bloon target;

        target = BloonFactory::BloonVector[0];
        for (Bloon b : BloonFactory::BloonVector)
        {
            if (Vector2Distance(b.GetCenter(), this->GetCenter()) > (float)_range)
            {
                continue;
            }
            if ((b.GetNowRouteTarget() > target.GetNowRouteTarget()) ||
                (b.GetNowRouteTarget() == target.GetNowRouteTarget() &&
                    Vector2Distance(b.GetCenter(),
                                    Map::GetRoute()[b.GetNowRouteTarget()]) <
                    Vector2Distance(target.GetCenter(),
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
        if (_isActive)
        {
            UpdateThrowable();

            if (!BloonFactory::BloonVector.empty() && shootTimecounter > shootDeltaTime)
            {
                Bloon target = focus();
                if (Vector2Distance(GetCenter(), target.GetCenter()) < static_cast<float>(_range))
                {
                    Shoot({static_cast<float>(target.GetLeft()), static_cast<float>(target.GetTop())});
                }
            }
            else
            {
                shootTimecounter += static_cast<float>(delayCount) / 100.F;
                // shootTimecounter += 1;
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
        auto next = throwablePool.front();
        Vector2 targetDirection = {
            (target.X - GetLeft()), target.Y - GetTop()
        };
        throwablePool.pop();
        next->SetActive(true);
        next->InitByCenter(GetCenter());
        next->SetMoveDirection(targetDirection.X, targetDirection.Y);
        throwables.push_back(next);
    }

    void Tower::SetThrowablePath(vector<string> name)
    {
        ThrowablePath = name;
    }

    // it is throwable factory
    void Tower::PushThrowablePool()
    {
        shared_ptr<Throwable> tmp = make_shared<Throwable>(Throwable());
        tmp->LoadBitmapByString({"resources/towers/bomb/bomb.bmp"}
                               ,RGB(255, 255, 255));
        throwablePool.push(tmp);
    }
}
