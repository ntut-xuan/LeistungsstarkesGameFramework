#pragma once
#include <queue>

#include "Bloon.h"
#include "Map.h"
#include "TowerFactory.h"

namespace Btd {
class BloonFactory {
public:
  static queue<Bloon> BloonPool;
  static vector<Bloon> BloonVector;
  static vector<UnitRound> BloonRound;
  static int BloonCounter;
  static int BloonTimer;
  static vector<string> balloonPath;

  static void SetNextRound(vector<UnitRound> rounds) {
    BloonRound = rounds;
    BloonCounter = 0;
    BloonTimer = 0;
  }

  static bool UpdateRound(int DeltaTime) {
    if (BloonTimer <= 0) {
      if (BloonCounter >= static_cast<int>(BloonRound.size())) {
        return true;
      }
      MakeBloon(BloonRound[BloonCounter].type);
      BloonTimer = BloonRound[BloonCounter].nextTime;
      BloonCounter++;
    } else {
      BloonTimer -= DeltaTime;
    }
    return false;
  }

  static void MakeBloon(Layer::NormalBloonLayer type) {
    Vector2 startPosition = Map::GetStartPosition();
    MakeBloonByPosition(type, startPosition, 0);
  }

  static void MakeBloonByPosition(Layer::NormalBloonLayer type,
                                  Vector2 startPosition, int nowRouteTarget) {
    if (BloonPool.empty()) {
      Bloon tmpBloon;
      tmpBloon.LoadBitmapByString(balloonPath, RGB(0, 0, 0));
      tmpBloon.SetLayer(0);
      tmpBloon.SetFrameIndexOfBitmap(0);
      tmpBloon.SetTopLeft(static_cast<int>(startPosition.X),
                          static_cast<int>(startPosition.Y));
      tmpBloon.SetActive(false);
      BloonPool.push(tmpBloon);
    }
    auto next = BloonPool.front();
    switch (type) {
    case Layer::black:
      next.SetFrameIndexOfBitmap(Layer::black);
      next.SetLayer(0);
      next.Setspeed(3);
      next.SetType(BloonType::black);
      break;
    case Layer::white:
      next.SetFrameIndexOfBitmap(Layer::white);
      next.SetLayer(0);
      next.Setspeed(3);
      next.SetType(BloonType::white);
      break;
    default:
      next.LoadBitmapByString(balloonPath, RGB(0, 0, 0));
      next.SetLayer(type);
      next.SetFrameIndexOfBitmap(type);
      next.Setspeed(3);
      // next.Setspeed(70);
      next.SetType(BloonType::normal);
      break;
    }
    next.SetNowRouteTarget(nowRouteTarget);
    next.SetTopLeft(static_cast<int>(startPosition.X),
                    static_cast<int>(startPosition.Y));
    next.SetActive(true);
    next.SetIsPoped(false);
    next.SetIsGoaled(false);
    BloonPool.pop();
    BloonVector.push_back(next);
  }

  static void UpdateBloon() {
    for (Bloon &b : BloonVector) {
      b.Update();
    }
    handlePopBalloon();
  }

  static void handlePopBalloon() {
    for (int i = 0; i < static_cast<int>(BloonVector.size()); i++) {
      Bloon b = BloonVector[i];
      if (BloonVector[i].IsPoped()) {
        BloonType::BloonType type = BloonVector[i].GetType();
        if (type == BloonType::black || type == BloonType::white) {
          int nowRouteTarget = BloonVector[i].GetNowRouteTarget();
          Vector2 position = {static_cast<float>(BloonVector[i].GetLeft()),
                              static_cast<float>(BloonVector[i].GetTop())};
          MakeBloonByPosition(Layer::yellow, position, nowRouteTarget);
          MakeBloonByPosition(Layer::yellow, position, nowRouteTarget);
        }
        BloonPool.push(BloonVector[i]);
        BloonVector.erase(BloonVector.begin() + i);
      }
    }
  }

  static int subLifeByGoalBloon() {
    int subLife = 0;
    for (int i = 0; i < static_cast<int>(BloonVector.size()); i++) {
      Bloon b = BloonVector[i];
      if (b.IsGoaled()) {
        BloonType::BloonType type = b.GetType();
        if (type == BloonType::black || type == BloonType::white) {
          subLife += 5;
        } else {
          subLife += b.GetLayer() + 1;
        }
        BloonPool.push(BloonVector[i]);
        BloonVector.erase(BloonVector.begin() + i);
      }
    }
    return subLife;
  }
};
} // namespace Btd
