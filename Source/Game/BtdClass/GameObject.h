#pragma once
#include "../../Library/gameutil.h"

namespace Btd
{
    struct Vector2
    {
        float X;
        float Y;
    };

    class GameObject : public game_framework::CMovingBitmap
    {
    private:
        bool _isActive = true;
        string _tag = "default";

    public:
        virtual ~GameObject() = default;
        virtual void Update() = 0;
        void SetActive(bool active);
        bool GetActive();
        void SetTag(string tag);
        string GetTag();
    };
}
