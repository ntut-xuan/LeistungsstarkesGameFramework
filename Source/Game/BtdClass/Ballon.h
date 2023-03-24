#pragma once
#include "GameObject.h"
#include "BtdUtil.h"
#include <list>
#include <map>

namespace Btd
{
    // ballon pop will not appear many bloon
    class Ballon : public GameObject
    {
    private:
        int nowRouteTarget = 0;
        float _speed = 3;
        int _layer = 0;
        bool _isPoped = false;
        BallonType::BallonType type = BallonType::normal;
        int _freezeTime;

    public:
        Ballon()
        {
            _layer = 0;
            _isPoped = false;
            _freezeTime = 0;
        };

        Ballon(int layer): _layer(layer)
        {
        }

        static bool resistDamegeMap[3][3];

        void SetNowRouteTarget(int target);

        void Setspeed(float speed);

        void SetType(BallonType::BallonType t)
        {
            type = t;
        }

        void Update() override;

        float GetSpeed();
        BallonType::BallonType GetType();

        void Move(vector<Vector2> route);

        void Pop(int damage, DamageType damageType);

        int GetNowRouteTarget()
        {
            return nowRouteTarget;
        }

        bool IsPoped();
        void SetIsPoped(bool poped);
        void SetLayer(int layer);
        void SetFreezeTime(int time);
    };
}
