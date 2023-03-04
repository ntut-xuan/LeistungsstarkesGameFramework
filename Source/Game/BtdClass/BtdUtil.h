#pragma once
#include "GameObject.h"

namespace Btd
{
    Vector2 Normailize(float x, float y)
    {
        float powSum = sqrt(x * x + y * y);
        return {x / powSum, y / powSum};
    }
}
