#ifndef MAP_H
#define MAP_H

#include "GameObject.h"
#include "BtdUtil.h"
#include "FactoryButton.h"

namespace Btd
{
    class Map : public GameObject
    {
    public:
        Map() = default;
        ~Map() override = default;
        void SetRoutesByMap(MapType::MapType type);
        const int InitMoney = 650;
        const int InitLives = 40;
        virtual void InitRoad(MapType::MapType type);
        void ShowRoad();
        virtual void InitBackground(MapType::MapType type);
        void ShowBackground();
        void InitFactoryButton();
        void ShowFactoryButton();
        void UpdateFactoryButton();
        void HandleButtonClicked(int* money);
        GameObject GetBackground();
        vector<vector<UnitRound>> GetRounds();
        void SetRounds(vector<vector<UnitRound>> round);
        static vector<vector<Vector2>> GetRoute();
        static void SetRoute(vector<vector<Vector2>>);
        bool IsOverLapRoad(GameObject target);

    protected:
        std::vector<GameObject> _road;
        GameObject _background;
        FactoryButton _factoryButton[5];
        static vector<vector<Vector2>> _route;
        vector<vector<UnitRound>> _rounds;
        GameObject _sidebar;
        vector<int> priceTable = {200,360,650,850,3600};
    };
}

#endif
