#include "stdafx.h"
#include "Throwable.h"

#include "BtdUtil.h"

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
        _moveDirection = Normailize(x, y);
    }


    Vector2 Throwable::GetMoveDirection() const
    {
        return _moveDirection;
    }

    /**
     * \brief  if speed set 1 iw wont move
     */
    void Throwable::Move()
    {
        Vector2 moveDirection = GetMoveDirection();
        float speed = GetSpeed();
        Vector2 deltaMove = {moveDirection.X * speed, moveDirection.Y * speed};
        int top = GetTop() + static_cast<int>(deltaMove.Y);
        int left = GetLeft() + static_cast<int>(deltaMove.X);
        SetTopLeft(left, top);
    }

    //TODO check touch baloon
}
