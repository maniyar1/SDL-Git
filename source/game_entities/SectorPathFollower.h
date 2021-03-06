#pragma once
#ifndef SECTOR_PATH_FOLLOWER_H
#define SECTOR_PATH_FOLLOWER_H
#include "../primitives/Rect.h"
#include "../wrappers/MovementWrapper.h"
#include "../wrappers/Texture.h"
#include "SectorPath.h"
#include "base/ThingBase.h"

class SectorPathFollower : public ThingBase {
   protected:
    MovementWrapper movement;

   public:
    Rect box;
    SectorPath mine;
    Texture texture;

    SectorPathFollower(Rect rect);
    ~SectorPathFollower();
    bool doesLineCollide(const Line& ray) const override;
    bool overlap(const Polygon& other) const override;
    bool overlap(const std::shared_ptr<ThingBase>& other) const override;
    bool wideOverlap(const Polygon& other) const override;
    double originDistance() const override;
    Point collideLine(const Line& ray) const override;
    Point getPosition() const override;
    Rect getBoundingRect() const override;
    void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) override;
    void update() override;
};
#endif
