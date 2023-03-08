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
        ~Map() override = default;
        const int InitMoney = 650;
        const int InitLives = 40;
        void InitRoad();
        void ShowRoad();
        void InitBackground();
        void ShowBackground();
        GameObject GetBackground();
        static vector<Vector2> GetRoute();
        static Vector2 GetStartPosition();
        static void SetStartPosition(Vector2);

    private:
        std::vector<GameObject> _road;
        GameObject _background;
        static vector<Vector2> _route;
        static Vector2 _startPosition;
    };
}

#endif
