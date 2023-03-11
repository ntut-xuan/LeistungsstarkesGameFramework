#pragma once
#include "GameObject.h"
#include "BtdUtil.h"

namespace Btd
{
    class Button : public GameObject 
    {
    public:
        Button() = default;
        ~Button() = default;
        bool IsCursorFocus();
        void SetClicked(bool clicked);
    protected:
        bool _isClicked = false;
    };
}
