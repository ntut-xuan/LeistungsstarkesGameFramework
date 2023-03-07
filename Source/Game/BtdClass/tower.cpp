#include "stdafx.h"
#include "tower.h"


//todo distance and direction set
//todo get the target ballon(need in route bloon list )
void Tower::Shoot(){
    if(throwablePool.isEmpty()||throwablePool.front().GetActive())	
    {
        PushThrowablePool(true);
    }else{
        auto next = throwablePool.front();
        next.SetActive(true);
        next.setTopLeft(throwLocal.X,throwLocal.Y);
        throwablePool.enqueue(throwablePool.dequeue());
    }
}
//todo when push can set top left
void Tower::PushThrowablePool(bool active){
    //var throwable = MakeThrowable();
    //throwable.SetActive(active);
    //throwablePool.enqueue(throwable);
}
void Tower::MakeThrowable(){
    // return throwableFactory.MakeThrowable(throwableName);
}