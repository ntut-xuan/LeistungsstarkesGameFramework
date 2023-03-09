#include "GameObject.h"
#include "BtdUtil.h"
#include "Throwable.h"
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
        int _layer = 1;

    public:
        Ballon() = default;

        Ballon(int layer): _layer(layer)
        {
        }

        static map<DamageType, bool> resistDamegeMap;
        void SetNowRouteTarget(int target);

        void Setspeed(float speed);


        void Update() override;

        float GetSpeed();

        void Move(vector<Vector2> route);

        void Pop(int damege, DamageType type)
        {
            if (resistDamegeMap[type])
            {
                _layer -= damege;
            }
            SetFrameIndexOfBitmap(_layer);
        }
        int GetNowRouteTarget(){
            return nowRouteTarget;
        }
    };
}
