//
// Created by Sam Serrels on 17/05/2017.
//

#include "Input.h"
#include "SDL_events.h"
namespace sb {
std::map<unsigned int, float> Input::keystatus = {};
bool Input::IsKeyDown(const unsigned int keycode) { return keystatus[keycode] > 0.0f; }

void Input::HandleKeyUp(const unsigned int keycode) { keystatus[keycode] = 0.0f; }

void Input::HandleKeyDown(const unsigned int keycode) { keystatus[keycode] = 255.0f; }

void Input::HandleSDLEvent(const SDL_Event &e) {
  switch (e.type) {
  case SDL_KEYDOWN:
    HandleKeyDown(e.key.keysym.sym);
    break;
  case SDL_KEYUP:
    HandleKeyUp(e.key.keysym.sym);
    break;
  default:
    break;
  }
}
}