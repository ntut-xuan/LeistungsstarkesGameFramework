#include "GameObject.h"
#include "BtdUtil.h"
#include <list>

namespace Btd
{
    class Ballon : public GameObject
    {
    private:
        int nowRouteTarget = 0;
        float _speed = 3;

    public:
        void SetNowRouteTarget(int target)
        {
            nowRouteTarget = target;
        }

        void Setspeed(float speed)
        {
            _speed = speed;
        }

        void Update() override
        {
            if (GetActive())
            {
                //todo if pop (layer==0) setactive(false)    
            }
        }

        float GetSpeed()
        {
            return _speed;
        }

        void Move(vector<Vector2> route)
        {
            Vector2 nowLocal;
            nowLocal.X = static_cast<float>(GetLeft());
            nowLocal.Y = static_cast<float>(GetTop());
            Vector2 moveDirection;
            if (CompareVector2(route[nowRouteTarget], nowLocal))
            {
                moveDirection = Normailize(route[++nowRouteTarget]);
            }
            else
            {
                moveDirection = Normailize(route[nowRouteTarget]);
            }
            float speed = GetSpeed();
            Vector2 deltaMove = {moveDirection.X * speed, moveDirection.Y * speed};
            int top = GetTop() + static_cast<int>(deltaMove.Y);
            int left = GetLeft() + static_cast<int>(deltaMove.X);
            SetTopLeft(left, top);
        }
    };
}
