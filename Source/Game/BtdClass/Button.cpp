#include "stdafx.h"
#include "Button.h"

namespace Btd
{
    bool Button::IsCursorFocus()
    {
        POINT p;
        GetCursorPos(&p);
        HWND hwnd = FindWindowA(NULL, "Game");
        ScreenToClient(hwnd, &p);
        if (GetLeft() < p.x && p.x < GetLeft() + GetWidth() &&
            GetTop() < p.y && p.y < GetTop() + GetHeight())
        {
            return true;
        }
        return false;
    }
    void Button::SetClicked(bool clicked)
    {
        _isClicked = clicked;
    }

    
}
