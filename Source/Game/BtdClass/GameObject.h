#pragma once
#include "../../Library/gameutil.h"

namespace Btd
{
    class GameObject : public game_framework::CMovingBitmap
    {
    private:
        bool _isActive = true;
        string _tag = "default";

    public:
        virtual ~GameObject() = default;
        virtual void Update() ;
        void SetActive(bool active);
        bool GetActive();
        void SetTag(string tag);
        string GetTag();
        void SetCenter(int x, int y);
    };
}
