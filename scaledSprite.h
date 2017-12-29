#ifndef SCALEDSPRITE__H
#define SCALEDSPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "multisprite.h"
#include "explodingSprite.h"
#include "health.h"
#include "smartSprite.h"

class ScaledSprite : public SmartSprite {
public:
  ScaledSprite(const std::string&,float);
  ScaledSprite(const ScaledSprite&);
  ~ScaledSprite();
  virtual void draw() const;
  inline float getScale()const{ return scale; }
  void  setScale(float s){ scale = s; }
  virtual void update(Uint32 ticks);
  void explode();
  void resetPosition();
  
private:
	float scale;
	ExplodingSprite* boom;
    bool explosion;
	ScaledSprite& operator=(const ScaledSprite&);

};

#endif
