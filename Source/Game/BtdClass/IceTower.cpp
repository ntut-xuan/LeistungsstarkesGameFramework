#include "stdafx.h"
#include "IceTower.h"

#include "IceGas.h"

namespace Btd
{
    IceTower::IceTower()
    {
        _range = 300;
        _iceScale = 1;
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

    void IceTower::TowerShow()
    {
        if (_isClicked)
        {
            this->RangeCircle.ShowBitmap((float)_range / 100.0);
        }
        for (int i=0; i<(int)throwables.size(); i++)
        {
            throwables[i]->SetCenter((int)GetCenter().X - static_cast<int>(75 * (_iceScale - 1)),
                (int)GetCenter().Y - static_cast<int>(75 * (_iceScale - 1)));
            throwables[i]->ShowBitmap(_iceScale);
        }
        this->ShowBitmap();
    }
}
