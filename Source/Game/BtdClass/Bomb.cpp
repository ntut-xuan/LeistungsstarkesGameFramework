#include "stdafx.h"
#include "Bomb.h"

#include "BloonFactory.h"

namespace Btd
{
    Bomb::Bomb()
    {
        SetAnimation(50, true);
    }

    void Bomb::DetectHitBalloon()
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
                if (GetFrameIndexOfBitmap() == 0)
                {
                    ToggleAnimation();
                    _existTime = 0;
                    _maxExistTime = 75;
                }
                else
                {
                    BloonFactory::BloonVector[i].Pop(1, _damageType);
                    cantHitBloons.push_back({&BloonFactory::BloonVector[i], 0});
                }
                _speed = 0;
            }
        }
    }
}
