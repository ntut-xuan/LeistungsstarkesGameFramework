#pragma once
#include "GameObject.h"


namespace Btd
{
    struct Vector2
    {
        float X;
        float Y;
    };

    Vector2 Normailize(float x, float y);
    Vector2 Normailize(Vector2);
    bool CompareVector2(Vector2 a,Vector2 b);
}
