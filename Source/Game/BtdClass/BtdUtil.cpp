#include "stdafx.h"
#include "BtdUtil.h"

namespace Btd
{
    Vector2 Normailize(float x, float y)
    {
        float powSum = sqrt(x * x + y * y);
        return {x / powSum, y / powSum};
    }

    Vector2 Normailize(Vector2 v)
    {
        float powSum = sqrt(v.X * v.X + v.Y * v.Y);
        return {v.X / powSum, v.Y / powSum};
    }

    bool CompareVector2(Vector2 a, Vector2 b)
    {
        return a.X == b.X && a.Y == b.Y;
    }

    Vector2 Vector2Add(Vector2 a, Vector2 b)
    {
        return {a.X + b.X, a.Y + b.Y};
    }

    Vector2 Vector2Sub(Vector2 a, Vector2 b)
    {
        return {a.X - b.X, a.Y - b.Y};
    }

    float Vector2Distance(Vector2 a, Vector2 b)
    {
        float x = a.X - b.X;
        float y = a.Y - b.Y;
        return sqrt(x * x + y * y);
    }
    int GetCursorPosX()
    {
        POINT p;
        GetCursorPos(&p);
        HWND hwnd = FindWindowA(NULL, "Game");
        ScreenToClient(hwnd, &p);
        return (int)p.x;
    }
    int GetCursorPosY()
    {
        POINT p;
        GetCursorPos(&p);
        HWND hwnd = FindWindowA(NULL, "Game");
        ScreenToClient(hwnd, &p);
        return (int)p.y;
    }
    
    bool IsOverlap(GameObject& character, GameObject& other)
    {
        if ((character.GetTop() + character.GetHeight() >= other.GetTop() &&
                character.GetTop() <= other.GetTop() + other.GetHeight())
            && (character.GetLeft() + character.GetWidth() >= other.GetLeft() &&
                character.GetLeft() <= other.GetLeft() + other.GetWidth()))
        {
            return true;
        }
        return false;
    }

}
