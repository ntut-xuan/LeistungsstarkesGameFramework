#include "stdafx.h"
#include "Throwable.h"

namespace Btd
{
    // void Throwable::SetSpeed(float speed) {
    //     _speed = speed;
    // }
    float Throwable::GetSpeed()
    {
        return _speed;
    }


    void Throwable::SetMoveDirection(float x, float y)
    {
        // _moveDirection = {x, y};
    }


    pair<float, float> Throwable::GetMoveDirection()
    {
        return _moveDirection;
    }

    void Throwable::Move()
    {
        pair<float, float> moveDirection = GetMoveDirection();
        float speed = GetSpeed();
        pair<float, float> dletaMove;
        dletaMove.first = moveDirection.first * speed;
        dletaMove.second = moveDirection.second * speed;
        int top = GetTop() + static_cast<int>(dletaMove.second);
        int left = GetLeft() + static_cast<int>(dletaMove.first);
        SetTopLeft(left, top);
    }

    //TODO check touch baloon
}
