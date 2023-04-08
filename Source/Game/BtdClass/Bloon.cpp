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
        if (GetActive() && _freezeTime <= 0)
        {
            Move(Map::GetRoute()[route]);
        }
        else if (_freezeTime > 0)
        {
            _freezeTime -= deltaTime;
        }
    }

    void Bloon::SetRoute(int n)
    {
        route = n;
    }

    int Bloon::Getroute()
    {
        return route;
    }

    float Bloon::GetSpeed()
    {
        return _speed;
    }

    void Bloon::Move(vector<Vector2> route)
    {
        Vector2 nowLocal = GetBottomCenter();
        Vector2 target = route[nowRouteTarget];
        if (static_cast<int>(target.X) == static_cast<int>(nowLocal.X) && static_cast<int>(target.Y) == static_cast<int>
            (nowLocal.Y))
        {
            if (nowRouteTarget != static_cast<int>(route.size()) - 1)
                nowRouteTarget++;
            else
            {
                SetActive(false);
                _isGoaled = true;
            }
        }
        target = route[nowRouteTarget];
        Vector2 deltaMove = Vector2Sub(target, nowLocal);
        Vector2 moveDirection = Normailize(deltaMove);
        float speed = GetSpeed();
        deltaMove = {moveDirection.X * speed, moveDirection.Y * speed};

        int x = static_cast<int>(nowLocal.X) + static_cast<int>(deltaMove.X);
        int y = static_cast<int>(nowLocal.Y) + static_cast<int>(deltaMove.Y);
        if (Vector2Distance({static_cast<float>(x), static_cast<float>(y)}, target) < speed * 2 / 3)
        {
            x = static_cast<int>(target.X);
            y = static_cast<int>(target.Y);
        }
        SetBottomCenter(x, y);
    }

    BloonType::BloonType Bloon::GetType()
    {
        return type;
    }

    void Bloon::Pop(int damage, DamageType damageType)
    {
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
        Setspeed(static_cast<float>(0.5 * _layer * _layer + _layer + 3));
    }

    bool Bloon::IsPoped()
    {
        return _isPoped;
    }

    void Bloon::SetIsPoped(bool poped)
    {
        _isPoped = poped;
    }

    void Bloon::SetIsGoaled(bool goaled)
    {
        _isGoaled = goaled;
    }

    void Bloon::SetLayer(int layer)
    {
        _layer = layer;
    }

    void Bloon::SetFreezeTime(int time)
    {
        _freezeTime = time;
    }

    bool Bloon::IsGoaled()
    {
        return _isGoaled;
    }

    int Bloon::GetLayer()
    {
        return _layer;
    }
}
