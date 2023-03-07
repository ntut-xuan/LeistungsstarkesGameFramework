#include "stdafx.h"
#include "tower.h"

namespace Btd
{
    Tower::Tower()
    {
        _isUpgrade[0] = false;
        _isUpgrade[1] = false;
        _isMovable = true;
    }

    bool Tower::IsMovable()
    {
        return _isMovable;
    }

    void Tower::SetNotMove()
    {
        _isMovable = false;
    }



}
