#include "stdafx.h"
#include "Throwable.h"

#include "BtdUtil.h"

namespace Btd
{
    void Throwable::Update()
    {
        _existTime += delayCount;
        if (_existTime > _maxExistTime)
        {
            SetActive(false);
        }
        if (GetActive())
        {
            Move();
        }
    }

    void Throwable::InitByCenter(Vector2 position)
    {
        _existTime = 0;
        _position = position;
        SetTopLeft(static_cast<int>(position.X) - GetWidth() / 2, static_cast<int>(position.Y) - GetHeight() / 2);
    }

    void Throwable::SetMaxExistTime(float t)
    {
        _maxExistTime = t;
    }


    void Throwable::SetSpeed(float speed)
    {
        _speed = speed;
    }

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
        _position = Vector2Add(_position, deltaMove);
        SetTopLeft(static_cast<int>(_position.X), static_cast<int>(_position.Y));
    }

    //TODO check touch baloon
}
