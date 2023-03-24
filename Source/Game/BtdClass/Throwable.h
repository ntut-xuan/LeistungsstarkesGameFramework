#pragma once
#include "GameObject.h"
#include "BtdUtil.h"
#include "Bloon.h"

namespace Btd
{

    class Throwable : public GameObject
    {
    protected:
        Vector2 _moveDirection;
        Vector2 _position = {0, 0};
        float _speed = 0;
        float _existTime = 0;
        float _maxExistTime = 0;
        float _damage = 0;
        int _maxPop = 0;
        int _poped = 0;
        DamageType _damageType;
        // throwable can't hit same balloon in one second
        vector<pair<Bloon*, int>> cantHitBloons;

    public:
        Vector2 GetMoveDirection() const;

        void Update() override;
        void SetMaxExistTime(float);
        void InitByCenter(Vector2 position);


        void Move();

        void SetSpeed(float speed);

        float GetSpeed();

        void SetMoveDirection(float x, float y);

        virtual void DetectHitBalloon ();

        void UpdateCantHitBloons ();
    };
}
