#pragma once
#include "GameObject.h"
#include "BtdUtil.h"
#include "Ballon.h"

namespace Btd
{

    class Throwable : public GameObject
    {
    private:
        Vector2 _moveDirection;
        float _speed = 0;
        float _existTime = 0;
        float _damage = 0;
        int _maxPop = 0;
        int _poped = 0;
        DamageType _damageType;
        vector<Ballon*> cantHitBloons;

    public:
        Vector2 GetMoveDirection() const;

        void Update() override
        {
            if (GetActive())
            {
                Move();
            }
            DetectHitBalloon();
        }

        void Move();

        void SetSpeed(float speed)
        {
            _speed = speed;
        }

        float GetSpeed();

        void SetMoveDirection(float x, float y);

        void DetectHitBalloon ();
    };
}
