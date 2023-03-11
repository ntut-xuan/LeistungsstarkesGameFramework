#include "stdafx.h"
#include "Tower.h"

namespace Btd
{
    Tower::Tower()
    {
        _isUpgrade[0] = false;
        _isUpgrade[1] = false;
        _isMovable = true;
    }

    bool Tower::IsMovable()
    {
        return _isMovable;
    }

    void Tower::SetIsMove(bool move)
    {
        _isMovable = move;
    }

    void Tower::Shoot()
    {
        if (throwablePool.empty() || throwablePool.front().GetActive())
        {
            PushThrowablePool(true);
        }
        else
        {
            auto next = throwablePool.front();
            throwablePool.pop();
            next.SetActive(true);
            next.SetTopLeft(static_cast<int>(throwLocal.X), static_cast<int>(throwLocal.Y));
            throwablePool.push(next);
        }
    }

    //todo when push can set top left
    void Tower::PushThrowablePool(bool active)
    {
        //var throwable = MakeThrowable();
        //throwable.SetActive(active);
        //throwablePool.enqueue(throwable);
    }

    void Tower::MakeThrowable()
    {
        // return throwableFactory.MakeThrowable(throwableName);


    }
}
