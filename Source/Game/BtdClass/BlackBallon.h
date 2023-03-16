#pragma once
#include "BallonFactory.h"

namespace Btd
{
    class BlackBallon : public Ballon
    {
    public:
        void Pop(int damage, DamageType type);
        
    };
    
}

