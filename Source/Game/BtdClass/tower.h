#ifndef TOWER_H
#define TOWER_H

#include "../../Library/gameutil.h"
#include "GameObject.h"
#include "Throwable.h"
#include <queue>
#include <string>
#include "Ballon.h"

namespace Btd
{
    class Tower : public GameObject
    {
    public:
        Tower();
        ~Tower() override = default;
        void Update() override;
        void SetUpgrade(int level);
        bool IsMovable();
        void SetIsMove(bool move);
        Vector2 getLocation();
        int getRange();
        void setUpdate(int level);
        void SetThrowablePath(string name);
        static string ThrowablePath;
        vector<Throwable> throwables;


        void SetThrowableLocal(Vector2 local)
        {
            throwLocal = local;
        }

        void TowerShow()
        {
            this->ShowBitmap();
            for (auto t : throwables)
            {
                t.ShowBitmap();
            }
        }

        float GetShootDeltaTime();
        void SetShootDeltaTime(float time);
        void Shoot(Vector2 target);
        void PushThrowablePool();
        void UpdateThrowable();
        float GetShootTimeCounter();
        void SetShootTimeCounter(float);

    private:
        bool _isUpgrade[2];
        bool _isMovable;
        int _speed;
        int _range;
        int _buyMoney;
        int _sellMoney;
        Vector2 _location;
        GameObject throwableFactory;
        queue<Throwable> throwablePool;
        float shootDeltaTime;
        float shootTimecounter;
        Vector2 throwLocal;

    protected:
        Ballon focus();
    };
}
#endif
