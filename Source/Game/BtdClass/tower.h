#ifndef TOWER_H
#define TOWER_H

#include "../../Library/gameutil.h"
#include "GameObject.h"
#include "Throwable.h"
#include <queue>
#include <string>

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
        void SetNotMove();
        Vector2 getLocation();
        int getRange();
        void setUpdate(int level);
        static string throwableName;
        vector<Throwable> throwables;

        void SetThrowableName(string name)
        {
            throwableName = name;
        }

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
        void SetShootDeltaTime(float time);

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
        Ballon focus();
        void Shoot();
        void PushThrowablePool(bool active);
        void MakeThrowable();
        void UpdateThrowable();
    };
}
#endif
