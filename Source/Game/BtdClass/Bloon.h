#pragma once
#include "GameObject.h"
#include "BtdUtil.h"
#include <list>
#include <map>

namespace Btd
{
    class Bloon : public GameObject
    {
    private:
        int nowRouteTarget = 0;
        float _speed = 3;
        int _layer = 0;
        bool _isPoped = false;
        BloonType::BloonType type = BloonType::normal;
        int _freezeTime;

    public:
        Bloon()
        {
            _layer = 0;
            _isPoped = false;
            _freezeTime = 0;
        };

        Bloon(int layer): _layer(layer)
        {
        }

        static bool resistDamegeMap[3][3];

        void SetNowRouteTarget(int target);

        void Setspeed(float speed);

        void SetType(BloonType::BloonType t)
        {
            type = t;
        }

        void Update() override;

        float GetSpeed();
        BloonType::BloonType GetType();

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
