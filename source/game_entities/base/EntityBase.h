#pragma once
#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H
#include "../../GameInstance.h"
#include "../../essential/util.h"
#include "../../primitives/Point.h"
#include "../../primitives/Rect.h"
#include "../../wrappers/Timer.h"
#include "ThingBase.h"

/* Base class for entities that exist for extended periods of time
 * with more complicated behavior patterns than a particle */
class EntityBase : public ThingBase {
   protected:
    // TODO: Friction should be based on math, do this at some point
    double angle, frictionAmount, maxVelocity;
    Point acceleration, velocity;
    Timer timer;

   public:
    EntityBase(int flags);
    ~EntityBase();
    double originDistance() const override;
    void accelerate(const Point& delta);
    void evalAngle(const Point& delta);
    void setAngle(const double& angle);
    void setFriction(const double& value);
    void setMaxVelocity(const double& value);
};
#endif
