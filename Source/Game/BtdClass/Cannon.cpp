#include "stdafx.h"
#include "Cannon.h"
#include "BloonFactory.h"
#include "Bomb.h"

namespace Btd
{
    void Cannon::Shoot(Vector2 target)
    {
        Tower::Shoot(target);
        // Vector2 targetDir = {target.X - GetCenter().X, target.Y - GetCenter().Y};
        // this->SetFrameIndexOfBitmap(GetFrameIndexByVector2(targetDir));
    }

    void Cannon::PushThrowablePool()
    {
        shared_ptr<Bomb> bomb = make_shared<Bomb>(Bomb());
        bomb->LoadBitmapByString(ThrowablePath, RGB(255, 255, 255));
        bomb->SetSpeed(5);
        throwablePool.push(bomb);
    }
}
