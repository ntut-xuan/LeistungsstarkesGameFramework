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
        const int InitMoney = 650;
        const int InitLives = 40;
        void InitRoad();
        void ShowRoad();
        void InitBackground();
        void ShowBackground();
        void InitFactoryButton();
        void ShowFactoryButton();
        void UpdateFactoryButton();
        void HandleButtonClicked();
        GameObject GetBackground();
        vector<vector<UnitRound>> GetRounds();
        void SetRounds(vector<vector<UnitRound>> round);
        static vector<Vector2> GetRoute();
        static Vector2 GetStartPosition();
        static void SetStartPosition(Vector2);
        static void SetRoute(vector<Vector2>);
        bool IsOverLapRoad(GameObject target);

    private:
        std::vector<GameObject> _road;
        GameObject _background;
        FactoryButton _factoryButton[5];
        static vector<Vector2> _route;
        static Vector2 _startPosition;

        vector<vector<UnitRound>> _rounds;
    };
}

#endif
