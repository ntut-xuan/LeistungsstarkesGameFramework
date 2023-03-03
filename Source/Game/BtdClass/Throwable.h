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
    pair<float, float> moveDirection;
    float speed = 0;
    float existTime = 0;
    float damage = 0;
    int maxPop = 0;
    int poped = 0;
    DamageType damageType;

public:
    pair<float, float> GetMoveDirection();
    void Update() override; //override
    void Move();
    float GetSpeed();
};
