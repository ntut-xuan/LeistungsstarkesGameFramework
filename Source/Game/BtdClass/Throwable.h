#pragma once
#include "GameObject.h"
#include "../../Library/gameutil.h"

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
    Throwable()
    {
        _moveDirection.first = 1;
        _moveDirection.second = 1;
    }

    pair<float, float> GetMoveDirection();
    void Update(); //override
    void Move();
    float GetSpeed();
};
