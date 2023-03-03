#pragma once
#include "GameObject.h"
#include "../../Library/gameutil.h"

namespace btd
{
    enum DamageType
    {
        ice,
        boom,
        normal
    };

    class Throwable : public GameObject
    {
    private:
        pair<float, float> _moveDirection;
        float _speed = 0;
        float _existTime = 0;
        float _damage = 0;
        int _maxPop = 0;
        int _poped = 0;
        DamageType _damageType;

    public:
        pair<float, float> GetMoveDirection();

        void Update()
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
