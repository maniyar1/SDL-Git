#pragma once
#include<math.h>
#include "../../wrappers/Timer.h"
#include "Path.h"

class CirclePath : public Path<Point> {
	protected:
		/* Standard Parametric Equation for a Cirle
		 * x = r * cos(t / a)
		 * y = r * sin(t / a)
		 * When CirclePath is created by a PathManager, its stored somewhere not doing anything
		 * When PathManager calls a Path it is then updated every frame until isFinished() returns false
		 * When called it checks how many milliseconds it has been since it was called, and if that number is 
		 * greater than 10ms it runs an update. Updates are defined as such
		 * dx = r / a * -sin(t / a)
		 * dy = r / a * cos(t / a)
		 * Where r is the intended radius and 2pi * a is the period */
		float outsideMult, periodModify;
		int maxTicks;
	public:
		CirclePath() : Path<Point>(NULL) {
			this->outsideMult = 0;
			this->periodModify = 0;
		}
	
		CirclePath(Point* target, int radius = 10, float periodModify = .5, int maxTicks = Path::SINGLE_LOOP) : Path<Point>(target) {
			this->outsideMult = radius * periodModify;
			this->periodModify = periodModify;
			if (maxTicks == Path::SINGLE_LOOP) {
				this->maxTicks = 2 * M_PI / periodModify;
			} else if (maxTicks == Path::REPEAT) {
				this->maxTicks = maxTicks;
			}
		};
		
		~CirclePath() {};
		
		bool isFinished() {
			if (this->ticksDone > this->maxTicks && this->maxTicks != Path::REPEAT) {
				return true;
			}
			return false;
		}
		
		void modify() {
			float tempdx = -this->outsideMult * sin(this->ticksDone * this->periodModify);
			float tempdy = this->outsideMult * cos(this->ticksDone * this->periodModify);
			*this->target += Point(tempdx, tempdy);
		}
		
};
