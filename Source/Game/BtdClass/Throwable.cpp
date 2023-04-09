#include "stdafx.h"
#include "Throwable.h"

#include <chrono>

#include "BtdUtil.h"
#include "BloonFactory.h"

namespace Btd
{
    void Throwable::Update()
    {
        if (static_cast<int>(_maxExistTime) != -1) // only bomb need
        {
            _existTime += static_cast<float>(deltaTime);
            if (_existTime > _maxExistTime)
            {
                SetActive(false);
            }
        }
        if (GetActive())
        {
            Move();
        }
        DetectHitBalloon();
        UpdateCantHitBloons();
    }

    void Throwable::InitByCenter(Vector2 position)
    {
        _existTime = 0;
        _position = position;
        SetTopLeft(static_cast<int>(position.X) - GetWidth() / 2, static_cast<int>(position.Y) - GetHeight() / 2);
    }

    void Throwable::SetDamageType(DamageType::DamageType damageType)
    {
        _damageType = damageType;
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


    void Throwable::DetectHitBalloon()
    {
        for (int i = 0; i < static_cast<int>(BloonFactory::BloonVector.size()); i++)
        {
            bool isHited = false;
            for (int j = 0; j < static_cast<int>(cantHitBloons.size()); j++)
            {
                if (cantHitBloons[j].first == &BloonFactory::BloonVector[i])
                {
                    isHited = true;
                    break;
                }
            }
            if (Btd::IsOverlap(*this, BloonFactory::BloonVector[i]) &&
                !isHited) //not in cant hit bloon)
            {
                BloonFactory::BloonVector[i].Pop(1, DamageType::Normal);
                cantHitBloons.push_back({&BloonFactory::BloonVector[i], 0});
                if (_canPenetrate == false)
                {
                    _isActive = false;
                    break;
                }
            }
        }
    }

    void Throwable::UpdateCantHitBloons()
    {
        for (int i = 0; i < static_cast<int>(cantHitBloons.size()); i++)
        {
            cantHitBloons[i].second += deltaTime;
            if (cantHitBloons[i].second > 1000)
            {
                cantHitBloons.erase(cantHitBloons.begin() + i);
            }
        }
    }

    void Throwable::SetPenetrate(bool penetrate)
    {
        _canPenetrate = penetrate;
    }

    Throwable::Throwable()
    {
        _maxExistTime = -1;
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
}
