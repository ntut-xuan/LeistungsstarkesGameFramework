#ifndef TOWER_H
#define TOWER_H

#include "../../Library/gameutil.h"
#include "GameObject.h"
#include "Throwable.h"
#include <queue>
#include <string>
#include "Bloon.h"

namespace Btd
{
    class Tower : public GameObject
    {
    public:
        Tower();
        ~Tower() override = default;
        Tower(Tower&&) = default;
        void Update() override;
        void SetUpgrade(int level);
        bool IsMovable();
        void SetIsMove(bool move);
        Vector2 getLocation();
        int GetRange();
        void setUpdate(int level);
        void SetThrowablePath(vector<string> name);
        vector<string> ThrowablePath;
        vector<shared_ptr<Throwable>> throwables;


        void SetThrowableLocal(Vector2 local);

        void TowerShow();

        float GetShootDeltaTime();
        void SetShootDeltaTime(float time);
        virtual void Shoot(Vector2 target);
        virtual void PushThrowablePool();
        void UpdateThrowable();
        float GetShootTimeCounter();
        void SetShootTimeCounter(float);
        GameObject RangeCircle;

    protected:
        bool _isUpgrade[2];
        bool _isMovable;
        // int _speed;
        int _range;
        int _buyMoney;
        int _sellMoney;
        Vector2 _location;
        GameObject throwableFactory;
        queue<shared_ptr<Throwable>> throwablePool;
        float shootDeltaTime;
        float shootTimecounter;
        Vector2 throwLocal;
        Bloon focus();
    };
}
#endif
