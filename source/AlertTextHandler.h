#pragma once
#ifndef ALERT_TEXT_HANDLER_H
#define ALERT_TEXT_HANDLER_H
#include <vector>

#include "wrappers/AlertText.h"
class AlertTextHandler {
   private:
    std::vector<AlertText> alerts;

   public:
    AlertTextHandler();
    ~AlertTextHandler();
    void addMessage(AlertText message);
    void drawHandler();
};
#endif
