#pragma once
#include "GameObject.h"
#include "../../Library/gameutil.h"

namespace Btd
{
    enum DamageType
    {
        Ice,
        Boom,
        Normal
    };

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

    public:
        Vector2 GetMoveDirection() const;

        void Update() override
        {
            if (GetActive())
            {
                Move();
            }
        }

        void Move();

        void SetSpeed(float speed)
        {
            _speed = speed;
        }

        float GetSpeed();

        void SetMoveDirection(float x, float y);
    };
}
