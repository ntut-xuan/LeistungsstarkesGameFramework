#include "stdafx.h"
#include "IceTower.h"

#include "IceGas.h"

namespace Btd
{
    IceTower::IceTower()
    {
        _range = 300;
        ThrowablePath = {"resources/towers/ice/ice.bmp"};
    }

    void IceTower::PushThrowablePool()
    {
        shared_ptr<IceGas> iceGas = make_shared<IceGas>(IceGas());
        iceGas->LoadBitmapByString(ThrowablePath, RGB(0, 0, 0));
        iceGas->SetSpeed(0);
        iceGas->SetMaxExistTime(150);
        iceGas->SetPenetrate(true);
        throwablePool.push(iceGas);
    }
}
