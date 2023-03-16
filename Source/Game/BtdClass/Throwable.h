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
        // throwable can't hit same balloon in one second
        vector<pair<Ballon*, long long>> cantHitBloons;

    public:
        Vector2 GetMoveDirection() const;

        void Update() override;

        void Move();

        void SetSpeed(float speed)
        {
            _speed = speed;
        }

        float GetSpeed();

        void SetMoveDirection(float x, float y);

        void DetectHitBalloon ();

        void UpdateCantHitBloons ();
    };
}
