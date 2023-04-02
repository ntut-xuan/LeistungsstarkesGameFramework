#include "stdafx.h"
#include "mapEasy.h"

namespace Btd
{
    void mapEasy::InitBackground()
    {
        _background.LoadBitmapByString({"resources/map/easy/map.bmp"});
        _background.SetTopLeft(0, 0);
    }
}
