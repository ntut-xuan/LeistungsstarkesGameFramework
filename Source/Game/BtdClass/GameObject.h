#pragma once
#include "../../Library/gameutil.h"

namespace btd
{
    class GameObject : public game_framework::CMovingBitmap
    {
    private:
        bool _isActive = true;
        string _tag = "default";

    public:
        void Update(); //todo virtual
        void SetActive(bool active);
        bool GetActive();
        void SetTag(string tag);
        string GetTag();
    };
}
