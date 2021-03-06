#pragma once
#ifndef SECTOR_PATH_H
#define SECTOR_PATH_H
#include <memory>
#include <vector>

#include "../GameInstance.h"
#include "../essential/random.h"
#include "Sector.h"
#include "base/ThingBase.h"

typedef std::shared_ptr<SectorBase> SectorPtr;

class SectorPath {
   protected:
    std::vector<SectorPtr> stored;
    ThingBase* target;

   public:
    SectorPath(ThingBase* target);
    SectorPath& operator=(const SectorPath& that);
    ~SectorPath();
    bool isFinished() const;
    int size();
    Point currentTarget(Point currentPosition);
    void clear();
    void createPath(SectorPtr startingSector, SectorPtr target);
    void draw();
};
#endif
