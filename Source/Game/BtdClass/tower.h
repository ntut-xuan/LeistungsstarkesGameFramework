#ifndef TOWER_H
#define TOWER_H

#include "../../Library/gameutil.h"
#include "GameObject.h"
#include "Throwable.h"
#include <queue>
#include <string>

class Tower : public game_framework::CMovingBitmap
{
public:
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
    bool _isUpdate[2];
    int _speed;
    int _range;
    int _buyMoney;
    int _sellMoney;
    Btd::GameObject throwableFactory;
    std::queue<Btd::Throwable> throwablePool;
    Btd::Vector2 throwLocal;
    void Shoot();
    void PushThrowablePool(bool active);
    void MakeThrowable();
};

#endif
