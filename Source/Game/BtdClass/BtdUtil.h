#pragma once
#include "GameObject.h"


namespace Btd
{
    struct Vector2
    {
        float X;
        float Y;
    };
    enum Attribute
    {
        dart,
        nail,
        ice,
        bomb,
        super
    };

    Vector2 Normailize(float x, float y);
    Vector2 Normailize(Vector2);
    bool CompareVector2(Vector2 a,Vector2 b);
    int GetCursorPosX();
    int GetCursorPosY();
    Vector2 Vector2Add(Vector2 a, Vector2 b);
    Vector2 Vector2Sub(Vector2 a, Vector2 b);
    float Vector2Distance(Vector2 a, Vector2 b);
    bool IsOverlap(GameObject& character, GameObject& other);
}
