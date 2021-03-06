#include <cmath>
#include "viewport.h"
#include "smartSprite.h"
#include "gamedata.h"


float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

SmartSprite::SmartSprite(const std::string& name,
                         int w, int h) :
MultiSprite(name),
currentMode(NORMAL),
 io(IOmod::getInstance()),
 playerPos(),
 playerWidth(w),
 playerHeight(h),
 safeDistance(Gamedata::getInstance().getXmlInt("safeDistance"))
 
{ }

SmartSprite::SmartSprite(const std::string& name) :
 MultiSprite(name),
 currentMode(NORMAL),
 io(IOmod::getInstance()),
 playerPos(),
 playerWidth(getFrame()->getWidth()/2),
 playerHeight(getFrame()->getHeight()/2),
 safeDistance(Gamedata::getInstance().getXmlInt("safeDistance"))
{}

SmartSprite::SmartSprite(const std::string& name,float scale) :
 MultiSprite(name,scale),
 currentMode(NORMAL),
 io(IOmod::getInstance()),
 playerPos(),
 playerWidth(getFrame()->getWidth()/2),
 playerHeight(getFrame()->getHeight()/2),
 safeDistance(Gamedata::getInstance().getXmlInt("safeDistance"))
{ }


void SmartSprite::goLeft()  {
  if (getX() > 0) setVelocityX( abs(getVelocityX()) );
}
void SmartSprite::goRight() {setVelocityX( -abs(getVelocityX()) );}
void SmartSprite::goUp()    { setVelocityY( fabs(getVelocityY()) ); }
void SmartSprite::goDown()  { setVelocityY( -fabs(getVelocityY()) ); }

void SmartSprite::draw() const {
  MultiSprite::draw();

}

void SmartSprite::update(Uint32 ticks) {
  MultiSprite::update(ticks);
  float x= getX()+getFrame()->getWidth()/2;
  float y= getY()+getFrame()->getHeight()/2;
  float ex= playerPos[0]+playerWidth/2;
  float ey= playerPos[1]+playerHeight/2;
  float distanceToEnemy = ::distance( x, y, ex, ey );

if(getName()=="bat")
{
  if  ( getMode()== EVADE) {
  
      if ( x < ex ) goLeft();
      if ( x > ex ) goRight();
      if ( y < ey ) goUp();
      if ( y > ey ) goDown();
    
  }
}
  else
  {
   
  if  ( currentMode == NORMAL) {
    if(distanceToEnemy < safeDistance) currentMode = EVADE;
  }
  if  ( currentMode== EVADE) {
    if(distanceToEnemy > safeDistance) currentMode=NORMAL;
    else {

      if ( x < ex ) goLeft();
      if ( x > ex ) goRight();
      if ( y < ey ) goUp();
      if ( y > ey ) goDown();
    }
  }
  
}
  
}

void SmartSprite::reset(){
	MultiSprite::reset();
}
