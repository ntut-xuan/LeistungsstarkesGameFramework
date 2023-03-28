#include "stdafx.h"
#include "DartMonkey.h"
#define M_PI 3.1415926

namespace Btd
{
    DartMonkey::DartMonkey()
    {
		_range = 160;
		ThrowablePath = {"resources/towers/monkey/dart_1.bmp", "resources/towers/monkey/dart_2.bmp", "resources/towers/monkey/dart_3.bmp"
		, "resources/towers/monkey/dart_4.bmp", "resources/towers/monkey/dart_5.bmp", "resources/towers/monkey/dart_6.bmp"
		, "resources/towers/monkey/dart_7.bmp", "resources/towers/monkey/dart_8.bmp"};
    	
    }

	int getAngleIndex(Vector2 dir)
    {
    	double angleInRadians = std::atan2(dir.Y, dir.X);
    	double angleInDegrees = (angleInRadians / M_PI) * 180.0;
    	// up:  -180 <----> 0
    	// down: 180 <----> 0
    	int index = 0;
    	double tmp = 0;
    	vector<int> rangeList = {0, 1, 3, 5, 7};  // quotient of angle / 22.5
    	vector<int> UpIndexList = {1, 8, 7, 6, 5};  // picture index
    	vector<int> downIndexList = {1, 2, 3, 4, 5};
    	vector<int> indexList;
    	if (angleInDegrees > 0)
    	{
    		indexList = downIndexList;
    	}
    	else
    	{
    		angleInDegrees *= (-1);
    		indexList = UpIndexList;
    	}
		tmp = angleInDegrees / 22.5;
		for (int i=0; i<5; i++)
		{
			if (tmp > rangeList[i])  index = indexList[i];
		}
    	TRACE("%d\n", index);
    	return index - 1;
    }

    void DartMonkey::Shoot(Vector2 target)
    {
	    Tower::Shoot(target);
        Vector2 targetDirection = {
            (target.X - (float)GetLeft()), target.Y - (float)GetTop()
        };
    	throwables.back()->SetFrameIndexOfBitmap(getAngleIndex(targetDirection));
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
    	dart->SetSpeed(5);
    	throwablePool.push(dart);
    }
}
