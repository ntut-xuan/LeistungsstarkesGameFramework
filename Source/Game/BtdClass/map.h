#ifndef MAP_H
#define MAP_H

#include "GameObject.h"
#include "BtdUtil.h"

namespace Btd
{
    class Map : public GameObject
    {
    public:
        Map() = default;
        ~Map() = default;
        const int InitMoney = 650;
        const int InitLives = 40;
        void InitRoad();
        void ShowRoad();
        void initBackground();
        void showBackground();
    private:
        std::vector<GameObject> _road;
        GameObject _background;
    };
}

#endif