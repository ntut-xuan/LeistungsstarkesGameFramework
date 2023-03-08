#ifndef TOWER_H
#define TOWER_H

#include "GameObject.h"
#include "BtdUtil.h"

namespace Btd
{
	class Tower : public GameObject
	{
	public:
		Tower();
		~Tower() = default;
		void SetUpgrade(int level);
		bool IsMovable();
		void SetNotMove();
		Vector2 getLocation();
		int getRange();
	private:
		bool _isUpgrade[2];
		bool _isMovable;
		int _speed;
		int _range;
		int _buyMoney;
		int _sellMoney;
		Vector2 _location;
	};
}

#endif