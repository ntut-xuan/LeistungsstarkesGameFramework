#include "stdafx.h"
#include "Throwable.h"

#include <chrono>

#include "BtdUtil.h"
#include "BallonFactory.h"

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

    void Throwable::DetectHitBalloon()
    {
        {
            for (int i=0; i<(int)BallonFactory::BallonVector.size(); i++)
            {
                // TODO: maybe need add timestamp
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
        int top = GetTop() + static_cast<int>(deltaMove.Y);
        int left = GetLeft() + static_cast<int>(deltaMove.X);
        SetTopLeft(left, top);
    }

    //TODO check touch baloon
}
