#include "stdafx.h"
#include "DartMonkey.h"

namespace Btd
{
    DartMonkey::DartMonkey()
    {
        _range = 160;
        ThrowablePath = {
            "resources/towers/monkey/dart_1.bmp", "resources/towers/monkey/dart_2.bmp",
            "resources/towers/monkey/dart_3.bmp", "resources/towers/monkey/dart_4.bmp",
            "resources/towers/monkey/dart_5.bmp", "resources/towers/monkey/dart_6.bmp",
            "resources/towers/monkey/dart_7.bmp", "resources/towers/monkey/dart_8.bmp"
        };
    }

    void DartMonkey::Shoot(Vector2 target)
    {
        Tower::Shoot(target);
        Vector2 targetDirection = {
            (target.X - GetCenter().X), target.Y - GetCenter().Y
        };
        throwables.back()->SetSpeed(20);
        throwables.back()->SetFrameIndexOfBitmap(GetFrameIndexByVector2(targetDirection));
        this->SetFrameIndexOfBitmap(GetFrameIndexByVector2(targetDirection));
    }

    void DartMonkey::PushThrowablePool()
    {
        auto dart = make_shared<Throwable>(Throwable());
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
