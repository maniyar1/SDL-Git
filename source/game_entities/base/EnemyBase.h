#pragma once
#include <SDL2/SDL.h>
#include <math.h>

#include <memory>
#include <vector>

#include "../../Dot.h"
#include "../../essential/constants.h"
#include "../../primitives/Vector.h"
#include "../../wrappers/MovementWrapper.h"
#include "../../wrappers/Texture.h"
#include "../../wrappers/Timer.h"
#include "EntityBase.h"

class EnemyBase : public ThingBase {
 protected:
  Texture texture;
  Timer pathTimer, timer;
  int width = 50;
  int height = 50;
  double angle = 0;
  double maxVelocity;
  bool turning = false;
  MovementWrapper mvmnt;

 public:
  EnemyBase(Point position = Point(0, 0), int flags = 0);
  virtual ~EnemyBase();
  virtual bool isLocationInvalid() const = 0;
  virtual Point getCenter() const = 0;
  virtual void update() = 0;
  virtual void draw(SDL_Renderer* renderer, Point offset = Point(0, 0));
  virtual void move(Point velocity);
  double getAngle() const;
  void turn(double delta);
  void toggleTurn();
  Point pathFindTo(Point pos = Point());
  friend std::ostream& operator<<(std::ostream& output, const EnemyBase& base);
};
