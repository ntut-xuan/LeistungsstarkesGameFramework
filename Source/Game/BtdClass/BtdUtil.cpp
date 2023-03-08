#include "stdafx.h"
#include "BtdUtil.h"

namespace Btd
{
    Vector2 Normailize(float x, float y)
    {
        float powSum = sqrt(x * x + y * y);
        return {x / powSum, y / powSum};
    }
    Vector2 Normailize(Vector2 v){
        float powSum = sqrt(v.X * v.X + v.Y * v.Y);
        return {v.X / powSum, v.Y / powSum};
    }
    bool CompareVector2(Vector2 a,Vector2 b){
        return a.X == b.X && a.Y==b.Y;
    }
    Vector2 Vector2Add(Vector2 a,Vector2 b){
        return {a.X + b.X ,a.Y+b.Y};
    }
    Vector2 Vector2Sub(Vector2 a,Vector2 b){
        return {a.X - b.X ,a.Y-b.Y};
    }
}
