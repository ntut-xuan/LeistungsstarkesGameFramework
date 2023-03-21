#pragma once


namespace game_framework
{
    class CMovingBitmap;
}

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

    enum BallonType
    {
        red = 0,
        blue,
        green,
        yelllow,
        black,
        white,
    };

    struct UnitRound
    {
        BallonType type;
        int nextTime;
    };

    enum DamageType
    {
        Ice,
        Boom,
        Normal
    };

    enum GameFlow
    {
        Prepare,
        Shoot,
        Win,
        GameEnd
    };

    Vector2 Normailize(float x, float y);
    Vector2 Normailize(Vector2);
    bool CompareVector2(Vector2 a, Vector2 b);
    int GetCursorPosX();
    int GetCursorPosY();
    Vector2 Vector2Add(Vector2 a, Vector2 b);
    Vector2 Vector2Sub(Vector2 a, Vector2 b);
    float Vector2Distance(Vector2 a, Vector2 b);
    Vector2 Spin45(Vector2 a);
    Vector2 Spin90(Vector2 a);
    bool isPointInBmp(POINT p, game_framework::CMovingBitmap target);
}
