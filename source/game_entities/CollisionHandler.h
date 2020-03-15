#pragma once
#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H
class CollisionHandler;
class GameInstance;
#include "../primitives/Line.h"
#include "../primitives/Rect.h"
#include<memory>
#include<vector>

// Interface to interact with the collidable objects from GameInstance
class CollisionHandler {
	private:
		GameInstance* parent;
	public:
		CollisionHandler(GameInstance* parent);
		~CollisionHandler();
		int size() const;
		bool doesCollideWith(const Rect& rect, void* pointer = NULL) const;
		bool doesCollideWith(const Line& ray, void* pointer = NULL) const;
		bool doesNotCollideWith(const Rect& rect, void* pointer = NULL) const;
		bool doesNotCollideWith(const Line& line, void* pointer = NULL) const;
		Point closestPointThatCollidesWith(const Line& ray, void* pointer = NULL) const;
};

#endif