#ifndef MAP_H
#define MAP_H

#include "GameObject.h"
#include "BtdUtil.h"
#include "FactoryButton.h"

namespace Btd
{
    class Map 
    {
    public:
        Map() = default;
        ~Map() = default;
        const int InitMoney = 650;
        const int InitLives = 40;
        void InitRoad();
        void ShowRoad();
        void InitBackground();
        void ShowBackground();
        void InitFactoryButton();
        void ShowFactoryButton();
        void UpdateFatoryButton();
        void HandleButtonClicked();
    private:
        std::vector<GameObject> _road;
        GameObject _background;
        FactoryButton _factoryButton[5];
    };
}

#endif