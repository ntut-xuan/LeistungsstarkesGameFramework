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
            if (Btd::IsOverlap(*this, BloonFactory::BloonVector[i]) &&
                !isHited) //not in cant hit bloon)
            {
                BloonFactory::BloonVector[i].Pop(0, DamageType::Ice);
                BloonFactory::BloonVector[i].SetFreezeTime(150);
                cantHitBloons.push_back({&BloonFactory::BloonVector[i], 0});
                if (_canPenetrate == false)
                {
                    _isActive = false;
                    break;
                }
            }
        }
    }
}
