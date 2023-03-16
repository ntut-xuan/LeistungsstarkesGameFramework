#pragma once
#include "BtdUtil.h"
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
        virtual void Update();
        void SetActive(bool active);
        bool GetActive();
        void SetTag(string tag);
        string GetTag();
        Vector2 GetCenter();
        void SetCenter(int x, int y);
    };
    bool IsOverlap(GameObject& character, GameObject& other);
}
