#ifndef HEALTH__H
#define HEALTH__H

#include <string>
#include <SDL.h>
#include <stdint.h>

class Health {
public:
  static Health& getInstance();
  ~Health();
  void HealthBarDraw() const;
  void increaseHealth();
  void decreaseHealth();
  void reset();
  SDL_Renderer* getRenderer() const { return renderer; }
  const int healthWidth;
  const int healthHeight;
  int health_x;
  int health_y;
    SDL_Rect healthRect;
  SDL_Rect healthRect1;
  int incDec;

private:

  SDL_Renderer* renderer;
  Health();
  Health(const Health&);
  Health& operator=(const Health&);
  SDL_Color textFontColor;
};

#endif
