#include "Throwable.h"
#include "stdafx.h"
#include "Ballon.h"

namespace Btd {
    map<DamageType, bool> Ballon::resistDamegeMap=
    {
        {DamageType::Normal,true},
        {DamageType::Ice,true},
        {DamageType::Boom,true}
    };

    void Ballon::SetNowRouteTarget(int target)
    {
        nowRouteTarget = target;
    }
    void Ballon::Setspeed(float speed)
    {
        _speed = speed;
    }

    void Ballon::Update() 
    {
        if (GetActive())
        {
            //todo if pop (layer==0) setactive(false)
            //Move(map.getroute());
        }
    }
    float Ballon::GetSpeed()
    {
        return _speed;
    }
    void Ballon::Move(vector<Vector2> route)
    {
        Vector2 nowLocal;
        nowLocal.X = static_cast<float>(GetLeft());
        nowLocal.Y = static_cast<float>(GetTop());
        Vector2 moveDirection;
        if (CompareVector2(route[nowRouteTarget], nowLocal))
        {
            if (nowRouteTarget != static_cast<int>(route.size()) - 1)
                nowRouteTarget++;
            else
            {
                SetActive(false);
                //todo  arrive goal ,hp-layer
            }
        }
        Vector2 deltaMove = Vector2Sub(route[nowRouteTarget], nowLocal);
        moveDirection = Normailize(deltaMove);
        float speed = GetSpeed();
        deltaMove = {moveDirection.X * speed, moveDirection.Y * speed};
        int top = GetTop() + static_cast<int>(deltaMove.Y);
        int left = GetLeft() + static_cast<int>(deltaMove.X);
        SetTopLeft(left, top);
    }
}