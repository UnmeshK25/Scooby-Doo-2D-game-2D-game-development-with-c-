#ifndef SMARTSPRITE__H
#define SMARTSPRITE__H
#include <iostream>
#include "multisprite.h"
#include "ioMod.h"

// SmartSprite is an observer of subject SubjectSprite, which
// in this example is a spinning star.

class SmartSprite : public MultiSprite {
public:
  SmartSprite(const std::string&,int w, int h);
  SmartSprite(const std::string&);
  SmartSprite(const std::string&,float);
  ~SmartSprite (){}
  void draw() const;
  void update(Uint32 ticks);
  void goLeft();
  void goRight();
  void goUp();
  void goDown();
  void reset();
  float getSafeDistance() { return safeDistance; }
  void setPlayerPos(const Vector2f& p) { playerPos = p; }
  Vector2f getPlayerPos(){return playerPos;}
  enum MODE {NORMAL, EVADE};
  MODE currentMode;
  MODE getMode(){return currentMode;}
  void setMode(MODE mode){currentMode=mode;}
  

private:
  
  IOmod& io;
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  float safeDistance;
  
  SmartSprite(const SmartSprite &);
  SmartSprite& operator=(const SmartSprite &rhs);
};

#endif
