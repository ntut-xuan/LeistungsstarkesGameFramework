#ifndef TOWER_H
#define TOWER_H

#include "../../Library/gameutil.h"
#include "GameObject.h"
#include "Throwable.h"
#include <queue>
#include <string>

class Tower : public game_framework::CMovingBitmap {
public:
	void setUpdate(int level);
	static string throwableName;
private:
	bool _isUpdate[2];
	int _speed;
	int _range;
	int _buyMoney;
	int _sellMoney;
	Btd::GameObject throwableFactory;	
	std::queue<Btd::Throwable> throwablePool;
	Btd::Vector2 throwLocal;
	void SetThrowableName(string name){
		throwableName = name;
	}

	void Shoot(){
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
	void PushThrowablePool(bool active){
		//var throwable = MakeThrowable();
		//throwable.SetActive(active);
		//throwablePool.enqueue(throwable);
	}

	void MakeThrowable(){
		// return throwableFactory.MakeThrowable(throwableName);
	}
};

#endif
