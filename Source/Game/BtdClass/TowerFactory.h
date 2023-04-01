#pragma once

#include "Cannon.h"
#include "DartMonkey.h"
#include "IceTower.h"
#include "NailMachine.h"

namespace Btd
{
    class TowerFactory
    {
    public:
        TowerFactory() {};
        ~TowerFactory() {};
        static vector<shared_ptr<Tower>> TowerVector;
        static void MakeTower (TowerType attribute);
        static void HandleTowerClicked();

    private: 
    };
}
