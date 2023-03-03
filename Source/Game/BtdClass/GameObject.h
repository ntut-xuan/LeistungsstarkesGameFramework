#pragma once
#include "../../Library/gameutil.h"

class GameObject : public game_framework::CMovingBitmap
{
private:
    bool _isActive;

public:
    void SetActive(bool active)
    {
        _isActive = active;
    }

    bool GetActive()
    {
        return _isActive;
    }
};
