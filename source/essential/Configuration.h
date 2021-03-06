#pragma once
#include <SDL2/SDL.h>

#include <fstream>
#include <iostream>
#include <map>
#include <string>

/* Modified -lightly- from http://www.cplusplus.com/forum/general/21115/ */
class Configuration {
   private:
    std::map<std::string, std::string> keyMap;
    std::map<std::string, int> configMap;

   public:
    Configuration();
    int operator[](std::string key);
    void output(std::ostream& output = std::cout);
    void reload();
};
