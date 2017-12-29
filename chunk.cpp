#include <iostream>
#include <cmath>

#include "chunk.h"

void Chunk::update(Uint32 ticks) { 
  float yincr = getVelocityY()* 2 * static_cast<float>(ticks) * 0.001;
  setY( getY()- yincr );
  float xincr = getVelocityX()*2 * static_cast<float>(ticks) * 0.001;
  setX( getX()- xincr );
  distance += ( hypot(xincr, yincr) );
  if (distance > maxDistance) tooFar = true;
}

