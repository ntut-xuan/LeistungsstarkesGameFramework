#include "stdafx.h"
#include "BtdUtil.h"
#include "Bloon.h"

#include "map.h"

namespace Btd
{
    //      normal ice boom
    //normal
    //black
    //white
    bool Bloon::resistDamegeMap[3][3] = {
        {true, true, true},
        {true, false, true},
        {true, true, false}
    };

    void Bloon::SetNowRouteTarget(int target)
    {
        nowRouteTarget = target;
    }

    void Bloon::Setspeed(float speed)
    {
        _speed = speed;
    }

    void Bloon::Update()
    {
        if (GetActive() && _freezeTime == 0)
        {
            Move(Map::GetRoute());
        }
        else if (_freezeTime > 0)
        {
            _freezeTime -= deltaTime;
        }
    }

    float Bloon::GetSpeed()
    {
        return _speed;
    }

    void Bloon::Move(vector<Vector2> route)
    {
        Vector2 nowLocal;
        nowLocal.X = static_cast<float>(GetLeft());
        nowLocal.Y = static_cast<float>(GetTop());
        Vector2 target = route[nowRouteTarget];
        if (static_cast<int>(target.X) == static_cast<int>(nowLocal.X) && static_cast<int>(target.Y) == static_cast<int>
            (nowLocal.Y))
        {
            if (nowRouteTarget != static_cast<int>(route.size()) - 1)
                nowRouteTarget++;
            else
            {
                SetActive(false);
                //todo  arrive goal ,hp-layer
            }
        }
        target = route[nowRouteTarget];
        Vector2 deltaMove = Vector2Sub(target, nowLocal);
        Vector2 moveDirection = Normailize(deltaMove);
        float speed = GetSpeed();
        deltaMove = {moveDirection.X * speed, moveDirection.Y * speed};
        int left = GetLeft() + static_cast<int>(deltaMove.X);
        int top = GetTop() + static_cast<int>(deltaMove.Y);
        if (Vector2Distance({static_cast<float>(left), static_cast<float>(top)}, target) < speed * 2 / 3)
        {
            left = static_cast<int>(target.X);
            top = static_cast<int>(target.Y);
        }
        SetTopLeft(left, top);
    }

    BloonType::BloonType Bloon::GetType()
    {
        return type;
    }

    void Bloon::Pop(int damage, DamageType damageType)
    {
        this;
        if (resistDamegeMap[type][damageType])
        {
            _layer -= damage;
        }
        if (_layer < 0)
        {
            _isPoped = true;
            return;
        }
        SetFrameIndexOfBitmap(_layer);
    }

    bool Bloon::IsPoped()
    {
        return _isPoped;
    }

    void Bloon::SetIsPoped(bool poped)
    {
        _isPoped = poped;
    }

    void Bloon::SetLayer(int layer)
    {
        _layer = layer;
    }

    void Bloon::SetFreezeTime(int time)
    {
        _freezeTime = time;
    }
}
