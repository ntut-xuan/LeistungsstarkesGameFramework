#ifndef TOWER_H
#define TOWER_H

#include "../../Library/gameutil.h"

class Tower : public game_framework::CMovingBitmap {
public:
	void setUpdate(int level);
private:
	bool _isUpdate[2];
	int _speed;
	int _range;
	int _buyMoney;
	int _sellMoney;

};

#endif