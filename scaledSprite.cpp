#include <iostream>
#include <cmath>
#include <functional>
#include "scaledSprite.h"
#include "explodingSprite.h"
#include "health.h"


ScaledSprite::~ScaledSprite(){
  if(boom){
    delete boom;
  }

}

ScaledSprite::ScaledSprite( const std::string& name, float sc1) :
  
   SmartSprite(name,sc1), 
  scale(sc1),
  boom(NULL),
  explosion(false)
{}

ScaledSprite::ScaledSprite( const ScaledSprite& s) :
   
  SmartSprite(NULL), 
  scale(s.scale),
  boom(s.boom),
  explosion(s.explosion)
{}


inline namespace{
  constexpr float SCALE_EPSILON = 2e-7;
}

void ScaledSprite::draw() const {
  if(getScale() < SCALE_EPSILON) return;
    if(boom && boom->chunkCount() != 0){

		static_cast<ExplodingSprite*> (boom)->draw();
		
	}
	else{
		frames[currentFrame]->draw(getX(), getY(),scale);
	}
}

void ScaledSprite::explode()
{

  if(!boom)
 {
	Sprite spr(getName(), getPosition(), getVelocity(), getFrame());
	explosion = true;
	if(boom) delete boom;
	boom = new ExplodingSprite(spr);
	if(getMode()== NORMAL)
	{
		setMode(EVADE);
		setPosition(Vector2f(getPlayerPos()[0]+300, getPlayerPos()[1]+100));
	}
 }

}

void ScaledSprite::update(Uint32 ticks)
{
    if(boom && boom->chunkCount() != 0){
		boom->update(ticks);
    if(boom && boom->chunkCount() == 0){
      delete boom;
        Health::getInstance().increaseHealth();
        boom = NULL;
        
    }
	}
	else{
		SmartSprite::update(ticks);
	}
}




