#include "stdafx.h"
#include "IceGas.h"

namespace Btd
{
    IceGas::IceGas()
    {
        _speed = 0;
    }

    void IceGas::DetectHitBalloon()
    {
        for (int i = 0; i < static_cast<int>(BloonFactory::BloonVector.size()); i++)
        {
            bool isHited = false;
            for (int j = 0; j < static_cast<int>(cantHitBloons.size()); j++)
            {
                if (cantHitBloons[j].first == &BloonFactory::BloonVector[i])
                {
                    isHited = true;
                    break;
                }
            }
            if (Vector2Distance(_realCenter, BloonFactory::BloonVector[i].GetCenter()) <= _range &&
                !isHited) //not in cant hit bloon)
            {
                BloonFactory::BloonVector[i].Pop(_freezeTime, DamageType::Ice);
                cantHitBloons.push_back({&BloonFactory::BloonVector[i], 0});
                if (_canPenetrate == false)
                {
                    _isActive = false;
                    break;
                }
            }
        }
    }

    void IceGas::SetRealCenter(Vector2 center)
    {
        _realCenter = center;
    }

    void IceGas::SetRange(int range)
    {
        _range = range;
    }

    void IceGas::SetFreezeTime(int freezeTime)
    {
        _freezeTime = freezeTime;
    }
}
