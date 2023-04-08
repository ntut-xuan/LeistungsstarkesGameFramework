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
        bool _isGoaled = false;
        BloonType::BloonType type = BloonType::normal;
        int _freezeTime;
        int route = 0;

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
        void SetRoute(int n);
        int Getroute();
        float GetSpeed();
        BloonType::BloonType GetType();

        void Move(vector<Vector2> route);

        void Pop(int damage, DamageType damageType);

        int GetNowRouteTarget()
        {
            return nowRouteTarget;
        }

        bool IsPoped();
        bool IsGoaled();
        void SetIsPoped(bool poped);
        void SetIsGoaled(bool goaled);
        void SetLayer(int layer);
        void SetFreezeTime(int time);
        int GetLayer();
    };
}
