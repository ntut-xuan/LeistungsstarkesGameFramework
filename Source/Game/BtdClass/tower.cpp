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
        _isClicked = true;
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
        for (int i = static_cast<int>(throwables.size()) - 1; i >= 0; i--)
        {
            throwables[i]->Update();
            if (Vector2Distance(throwables[i]->GetCenter(), GetCenter()) > static_cast<float>(_range) + 70)
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
        Bloon target = BloonFactory::BloonVector[0];
        // first 'for' can detect the first bloon in range
        // second 'for' decide the proper bloon to shoot
        for (int i = 0; i < static_cast<int>(BloonFactory::BloonVector.size()); i++)
        {
            if (Vector2Distance(BloonFactory::BloonVector[i].GetCenter(), this->GetCenter()) <= static_cast<float>(
                _range))
            {
                target = BloonFactory::BloonVector[i];
            }
        }
        for (int i = 0; i < static_cast<int>(BloonFactory::BloonVector.size()); i++)
        {
            if (Vector2Distance(BloonFactory::BloonVector[i].GetCenter(), this->GetCenter()) <= static_cast<float>(
                _range))
            {
                auto b = BloonFactory::BloonVector[i];
                if ((BloonFactory::BloonVector[i].GetNowRouteTarget() > target.GetNowRouteTarget()) ||
                    (BloonFactory::BloonVector[i].GetNowRouteTarget() == target.GetNowRouteTarget() &&
                        Vector2Distance(BloonFactory::BloonVector[i].GetCenter(),
                                        Map::GetRoute()[b.Getroute()][b.GetNowRouteTarget()]) <
                        Vector2Distance(target.GetCenter(),
                                        Map::GetRoute()[b.Getroute()][b.GetNowRouteTarget()])))
                {
                    target = BloonFactory::BloonVector[i];
                }
            }
        }
        return target;
    }

    void Tower::SetShootTimeCounter(float tome)
    {
        shootTimecounter = tome;
    }

    void Tower::TowerShow()
    {
        if (_isClicked)
        {
            this->RangeCircle.ShowBitmap(static_cast<float>(_range) / 100.0);
        }
        this->ShowBitmap();
        for (int i = 0; i < static_cast<int>(throwables.size()); i++)
        {
            throwables[i]->ShowBitmap();
        }
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
        RangeCircle.SetCenter(static_cast<int>(GetCenter().X) - (_range - 100),
                              static_cast<int>(GetCenter().Y) - (_range - 100));
        if (_isActive)
        {
            UpdateThrowable();

            if (!BloonFactory::BloonVector.empty() && shootTimecounter > shootDeltaTime)
            {
                Bloon target = focus();
                if (Vector2Distance(GetCenter(), target.GetCenter()) < static_cast<float>(_range))
                {
                    Shoot({(target.GetCenter().X), (target.GetCenter().Y)});
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
            target.X - GetCenter().X, target.Y - GetCenter().Y
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
        auto tmp = make_shared<Throwable>(Throwable());
        tmp->LoadBitmapByString({"resources/towers/bomb/bomb.bmp"}
                                ,RGB(255, 255, 255));
        throwablePool.push(tmp);
    }
}
