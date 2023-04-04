#include "StdAfx.h"

#include "string"
#include "vector"

#include "BtdUtil.h"
#include "GameObject.h"
#include "map.h"

namespace Btd
{
    void Map::InitRoad(MapType::MapType type)
    {
        int roadSize[3];
        string roadPath[3] = {"easy", "medium", "hard"};
        vector<Vector2> location[3] =
        {
            {
                {0, 340}, {248, 143}, {131, 140},
                {132, 26}, {132, 22}, {604, 23},
                {414, 152}, {415, 155}, {412, 288},
                {617, 288}, {138, 436}, {141, 436},
                {144, 652}, {327, 510}, {327, 512},
                {502, 507}
            },
            {
                {0, 320}, {105, 124}, {170, 124},
                {285, 190}, {285, 390}, {43, 510},
                {43, 575}, {110, 636}, {620, 426},
                {429, 428}, {429, 249}, {496, 249},
                {622, 46}, {368, 48}, {368, 0}
            },
            {
            }
        };
        for (int i =0; i<3; i++)
        {
            roadSize[i] = (int)location[i].size();
        }
        for (int i = 0; i < roadSize[type]; i++)
        {
            GameObject tmpRoad;
            string filePath = "resources/map/" + roadPath[type] + "/roads/road_" + std::to_string(i + 1) + ".bmp";
            tmpRoad.LoadBitmapByString({filePath});
            tmpRoad.SetHeight(tmpRoad.GetHeight()-10);
            tmpRoad.SetWidth(tmpRoad.GetWidth()-10);
            tmpRoad.SetTopLeft(static_cast<int>(location[type][i].X), static_cast<int>(location[type][i].Y));
            tmpRoad.SetTag("road");
            _road.push_back(tmpRoad);
        }
    }

    void Map::ShowRoad()
    {
        for (int i = 0; i < (int)_road.size(); i++)
        {
            _road[i].ShowBitmap();
        }
    }

    void Map::InitBackground(vector<string> backgroundBmp)
    {
        _background.LoadBitmapByString(backgroundBmp);
        _background.SetTopLeft(0, 0);
    }

    void Map::ShowBackground()
    {
        _background.ShowBitmap();
    }

    void Map::InitFactoryButton()
    {
        vector<string> filePath = {
            "resources/button/button_monkey.bmp", "resources/button/button_nail.bmp", "resources/button/button_ice.bmp",
            "resources/button/button_bomb.bmp", "resources/button/button_super.bmp"
        };
        vector<TowerType> attributes = {dart, nail, ice, bomb, super};
        float start = 740, space = 47;
        vector<Vector2> locations = {
            {start, 300}, {start + space * 1, 300}, {start + space * 2, 300},
            {start + space * 3, 300}, {start + space * 4, 300}
        };
        for (int i = 0; i < 5; i++)
        {
            _factoryButton[i].LoadBitmapByString({filePath[i]});
            _factoryButton[i].SetAttribute(attributes[i]);
            _factoryButton[i].SetTopLeft(static_cast<int>(locations[i].X), static_cast<int>(locations[i].Y));
        }
    }

    void Map::ShowFactoryButton()
    {
        for (int i = 0; i < 5; i++)
        {
            _factoryButton[i].ShowBitmap();
        }
    }

    void Map::UpdateFatoryButton()
    {
        for (int i = 0; i < 5; i++)
        {
            _factoryButton[i].Update();
        }
    }

    void Map::HandleButtonClicked()
    {
        for (int i = 0; i < 5; i++)
        {
            if (_factoryButton[i].IsCursorFocus())
            {
                _factoryButton[i].SetClicked(true);
            }
        }
    }

    GameObject Map::GetBackground()
    {
        return _background;
    }

    vector<Vector2> Map::_route = {{100, 100}, {110, 110}, {0, 100}, {200, 200}};

    vector<Vector2> Map::GetRoute()
    {
        return _route;
    }

    void Map::SetRoute(vector<Vector2> route)
    {
        _route = route;
    }

    bool Map::IsOverLapRoad(GameObject target)
    {
        for (int i=0; i<(int)_road.size(); i++)
        {
            if(Btd::IsOverlap(_road[i], target))
            {
                return true;
            }
        }
        return false;
    };

    Vector2 Map::_startPosition = {0, 0};

    void Map::SetStartPosition(Vector2 StartPosition)
    {
        _startPosition = StartPosition;
    }

    Vector2 Map::GetStartPosition()
    {
        return _startPosition;
    }

    vector<vector<UnitRound>> Map::GetRounds()
    {
        return _rounds;
    }

    void Map::SetRounds(vector<vector<UnitRound>> round)
    {
        _rounds = round;
    }
}
