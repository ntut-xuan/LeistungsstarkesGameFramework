#include "stdafx.h"
#include "tower.h"


//todo distance and direction set
//todo get the target ballon(need in route bloon list )
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
