//
// Created by Sam Serrels on 17/05/2017.
//

#pragma once
#include "SDL_events.h"
#include <map>
namespace sb {

class Input {

public:
  static bool IsKeyDown(const unsigned int keycode);
  static void HandleKeyUp(const unsigned int keycode);
  static void HandleKeyDown(const unsigned int keycode);
  static void HandleSDLEvent(const SDL_Event &e);

protected:
  static std::map<unsigned int, float> keystatus;
};
}

#pragma once
