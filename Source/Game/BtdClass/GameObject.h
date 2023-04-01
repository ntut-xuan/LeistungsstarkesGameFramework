#pragma once
#include "BtdUtil.h"
#include "../../Library/gameutil.h"

namespace Btd
{
    class GameObject : public game_framework::CMovingBitmap
    {
    protected:
        bool _isActive = true;
        string _tag = "default";
        int deltaTime = 10;
        bool _isClicked;

    public:
        virtual ~GameObject() = default;
        virtual void Update();
        void SetActive(bool active);
        bool GetActive();
        void SetTag(string tag);
        string GetTag();
        Vector2 GetCenter();
        void SetCenter(int x, int y);
        bool IsCursorFocus();
        void SetClicked(bool clicked);
        void SetHeight(int height);
        void SetWidth(int width);
    };
    bool IsOverlap(GameObject& character, GameObject& other);
}
