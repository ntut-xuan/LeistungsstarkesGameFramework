#include "stdafx.h"
#include "DartMonkey.h"

namespace Btd
{
    DartMonkey::DartMonkey()
    {
		_range = 160;
		ThrowablePath = {"resources/towers/monkey/dart.bmp"};
    }

    void DartMonkey::PushThrowablePool()
    {
	    shared_ptr<Throwable> dart = make_shared<Throwable>(Throwable());
    	if (_isUpgrade[0])
    	{
    		// dart monkey first upgrade can let throwable penetrate
    		dart->SetPenetrate(true);
    	}
    	dart->LoadBitmapByString(ThrowablePath, RGB(255, 255, 255));
    	throwablePool.push(dart);
    }
}
