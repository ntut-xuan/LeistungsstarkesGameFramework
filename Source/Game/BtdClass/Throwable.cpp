#include "stdafx.h"
#include "Throwable.h"

#include <chrono>

#include "BtdUtil.h"
#include "BallonFactory.h"

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
        DetectHitBalloon();
        UpdateCantHitBloons();
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

    void Throwable::DetectHitBalloon()
    {
        {
            for (int i=0; i<(int)BallonFactory::BallonVector.size(); i++)
            {
                for (int j=0; j<(int)cantHitBloons.size(); j++)
                {
                    if (cantHitBloons[j].first == &BallonFactory::BallonVector[i])
                    {
                        return;
                    }
                }
                if (Btd::IsOverlap(*this, BallonFactory::BallonVector[i]))
                {
                    BallonFactory::BallonVector[i].Pop(1, Normal);
                    long long nowTime = std::chrono::system_clock::to_time_t((std::chrono::system_clock::now()));
                    cantHitBloons.push_back({&BallonFactory::BallonVector[i], nowTime});
                }    
            }
        }
    }

    void Throwable::UpdateCantHitBloons()
    {
        for (int i=0; i<(int)cantHitBloons.size(); i++)
        {
            long long nowTime = std::chrono::system_clock::to_time_t((std::chrono::system_clock::now()));
            long long delta = nowTime - cantHitBloons[i].second;
            if (delta > 1)
            {
                cantHitBloons.erase(cantHitBloons.begin()+i);
            }
        }
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
