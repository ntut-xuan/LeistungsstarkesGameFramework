#include "StdAfx.h"

#include "string"
#include "vector"

#include "BtdUtil.h"
#include "GameObject.h"
#include "map.h"

namespace Btd
{
	void Map::InitRoad()
	{
		std::string roadFileName;
		vector<Btd::Vector2> location{{0, 320}, {105, 124}, {170, 124},
										   {285, 190}, {285, 390}, {43, 510},
										   {43, 575}, {110, 636}, {620, 426},
										   {429, 428}, {429, 249}, {496, 249},
										   {622, 46}, {368, 48}, {368, 0}};
		for (int i = 0; i < 15; i++) {
			GameObject tmpRoad;
			string filePath = "resources/roads/road_" + std::to_string(i+1) + ".bmp";
			tmpRoad.LoadBitmapByString({ filePath});
			tmpRoad.SetTopLeft((int)location[i].X, (int)location[i].Y);
			tmpRoad.SetTag("road");
			_road.push_back(tmpRoad);
		}
	}

	void Map::ShowRoad()
	{
		for (int i=0; i<15; i++)
		{
			_road[i].ShowBitmap();
		}	
	}

	void Map::initBackground()
	{
		_background.LoadBitmapByString({ "resources/map.bmp" });
		_background.SetTopLeft(0, 0);
	}

	void Map::showBackground()
	{
		_background.ShowBitmap();
	}



}
