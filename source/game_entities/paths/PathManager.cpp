#include "PathManager.h"

PathManager::PathManager(EnemyBase* target)
    : target(target), repeat(false), index(0) {}

PathManager::~PathManager() { paths.clear(); }

bool PathManager::paused() { return this->paths[this->index]->isPaused(); }

void PathManager::addPath(std::shared_ptr<Path> path) {
    path->setTarget(this->target);
    this->paths.push_back(path);
}

void PathManager::removePath(int index) {
    if (this->index < this->paths.size()) {
        this->paths.erase(this->paths.begin() + index);
    }
}

void PathManager::setRepeat(bool val) { this->repeat = val; }

void PathManager::update() {
    if (this->index < this->paths.size()) {
        if (this->paths[this->index]->isFinished()) {
            this->paths[this->index]->stop();
            this->index++;
            if (this->index >= this->paths.size() && this->repeat) {
                this->index = 0;
            }
        }
        if (this->paths[this->index]->isStarted()) {
            this->paths[this->index]->update();
        } else {
            this->paths[this->index]->start();
        }
    }
}

void PathManager::pause() { this->paths[this->index]->pause(); }

void PathManager::unpause() { this->paths[this->index]->unpause(); }
