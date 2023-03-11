#ifndef TOWER_H
#define TOWER_H

#include "../../Library/gameutil.h"
#include "GameObject.h"
#include "Throwable.h"
#include <queue>
#include <string>

namespace Btd {
    class Tower : public GameObject
    {
    public:
        Tower();
        ~Tower() = default;
        void SetUpgrade(int level);
        bool IsMovable();
        void SetIsMove(bool move);
        Vector2 getLocation();
        int getRange();
        void setUpdate(int level);
        static string throwableName;

        void SetThrowableName(string name)
        {
            throwableName = name;
        }

        void SetThrowableLocal(Btd::Vector2 local)
        {
            throwLocal = local;
        }

    private:
        bool _isUpgrade[2];
        bool _isMovable;
        int _speed;
        int _range;
        int _buyMoney;
        int _sellMoney;
        Vector2 _location;
        GameObject throwableFactory;
        queue<Btd::Throwable> throwablePool;
        Vector2 throwLocal;
        void Shoot();
        void PushThrowablePool(bool active);
        void MakeThrowable();
    };

}
#endif
