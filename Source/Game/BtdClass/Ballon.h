#include "GameObject.h"
#include "BtdUtil.h"
#include <list>

namespace Btd {
    class Ballon :public GameObject
    {
        private:
        int nowRouteTarget;
        float _speed ;
        public:
        void Update() override{
            if(GetActive()){
                //todo if pop (layer==0) setactive(false)    
            }

        }
        float GetSpeed(){
            return  _speed;
        }
        void Move(vector<Vector2> route)
        {
            Vector2 nowLocal ;
            nowLocal.X = GetLeft();
            nowLocal.Y = GetTop();
            Vector2 moveDirection ;
            if(CompareVector2( route[nowRouteTarget] ,nowLocal)){
                moveDirection =Normailize( route[++nowRouteTarget]);
            }else{
                moveDirection =Normailize( route[nowRouteTarget]);
            }
            float speed = GetSpeed();
            Vector2 deltaMove = {moveDirection.X * speed, moveDirection.Y * speed};
            int top = GetTop() + static_cast<int>(deltaMove.Y);
            int left = GetLeft() + static_cast<int>(deltaMove.X);
            SetTopLeft(left, top);
        }

    }
}