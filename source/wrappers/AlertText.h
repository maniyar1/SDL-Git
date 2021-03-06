#pragma once
#ifndef ALERT_TEXT_H
#define ALERT_TEXT_H
#include <SDL2/SDL.h>

#include <string>

#include "../primitives/Point.h"
#include "Font.h"
#include "Timer.h"
class AlertText {
   private:
    Font font;
    SDL_Color color;
    Point position;
    std::string message;
    Timer timer;
    bool finished;
    float maxMilliseconds;

   public:
    AlertText(std::string text, Point position, SDL_Color color,
              int textSize = 20, float milliseconds = 1000,
              std::string filename = "font.ttf");
    ~AlertText();
    AlertText(const AlertText& other);
    AlertText& operator=(const AlertText& other);
    bool isDone();
    void render();
};
#endif
