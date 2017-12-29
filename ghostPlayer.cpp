#include "ghostPlayer.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "viewport.h"
#include "explodingSprite.h"
#include "health.h"
#include "hud.h"
#include "clock.h"
#include "collisionStrategy.h"


GhostPlayer::GhostPlayer( const std::string& name) :
  MultiSprite(name),
  explosion(false),
  life_cnt(3),
  initVelocity(getVelocity()),
   boom(NULL),
  godMode(false),
  observers(0)
{}

  GhostPlayer::GhostPlayer(const GhostPlayer& s) :
  MultiSprite(s),
  explosion(s.explosion),
  life_cnt(s.life_cnt),
   initVelocity(s.initVelocity),
   boom(s.boom),
  godMode(s.godMode),
  observers(s.observers)

{}


void GhostPlayer::stop(){
    setVelocityX(0.5 * getVelocityX());
    setVelocityY(0);
}

void GhostPlayer::gotoLeft(){
  if( getX() > 0){
	  setVelocityX(initVelocity[0]);
  }
}

void GhostPlayer::gotoRight(){
  if( getX() < worldWidth-frameWidth){
	  setVelocityX(-initVelocity[0]);
  }
}

void GhostPlayer::gotoUp(){
  if( getY() > 0){
	  setVelocityY(-initVelocity[1]);
  }
}

void GhostPlayer::gotoDown(){
  if( getY() < worldHeight-frameHeight){
	  setVelocityY(initVelocity[1]);
  }
}

void GhostPlayer::draw() const{
	if((Health::getInstance().healthRect1.w)==0)
    {
		Hud::getInstance().HudLoss();
		Clock::getInstance().pause();
    }

	if(boom && boom->chunkCount() != 0){
		static_cast<ExplodingSprite*> (boom)->draw();
		if(life_cnt==0)
		{
			Hud::getInstance().HudLoss();
			Clock::getInstance().pause();
		}
		Hud::getInstance().HudLife(getLife());
	}
	else
	{
		MultiSprite::draw();
	}

}

void GhostPlayer::explode()
{
  if(!godMode && !boom)
 {
	   Sprite spr(getName(), getPosition(), getVelocity(), getFrame());
	    explosion = true;
	     boom = new ExplodingSprite(spr);
	     setPosition(Vector2f(getPosition()[0]+200, getPosition()[1]-100));
	    
     }

}

void GhostPlayer::resetPosition(){
   setX(Gamedata::getInstance().getXmlInt(getName()+"/startLoc/x"));

   setY(Gamedata::getInstance().getXmlInt(getName()+"/startLoc/y"));
   setVelocity(Vector2f(Gamedata::getInstance().getXmlInt(getName()+"/speedX"),
                    Gamedata::getInstance().getXmlInt(getName()+"/speedY")));

   explosion = false;
   boom=NULL;
   if(life_cnt<3)
   setLife(3);

}

void GhostPlayer::update(Uint32 ticks) {
  if(boom){
	  
    boom->update(ticks);
    if(boom->chunkCount() == 0)
    {
      delete boom;
       explosion = false;
      life_cnt--;
      setLife(life_cnt);
      boom = NULL;
     
  }

}
else
{
	advanceFrame(ticks);
    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.003;

    setPosition(getPosition() + incr);
    notify();
    if( getX() < 0){
	  setVelocityX( abs( getVelocityX()));
    }
    if( getX() > worldWidth-frameWidth){
	  setVelocityX( -abs( getVelocityX()));
    }
    if( getY() >= 0){
	  setVelocityY(abs( getVelocityY()));
    }
    if( getY() <= worldHeight-frameHeight){
	  setVelocityY(-abs( getVelocityY()));
    }
    stop();
  }
}


void GhostPlayer::detach( SmartSprite* o ) {
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      ptr = observers.erase(ptr);
     
      return;
    }
    ++ptr;
  }
}

void GhostPlayer::notify() {

  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    (*ptr)->setPlayerPos( getPosition() );
    ++ptr;
  }
}


