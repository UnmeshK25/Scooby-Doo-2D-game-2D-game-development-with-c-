#include "shootingSprite.h"
#include "gamedata.h"

ShootingSprite::ShootingSprite(const std::string& name) :
  GhostPlayer(name),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") )
{ }

ShootingSprite::ShootingSprite(const ShootingSprite& s) :
  GhostPlayer(s),
  bulletName(s.bulletName),
  bullets(s.bullets),
  minSpeed(s.minSpeed)
{ }

ShootingSprite::~ShootingSprite(){

}
void ShootingSprite::shoot() {
if(!explosion)
{

	Vector2f vel = getVelocity();
    float x;
    float y = getY()+ frameHeight/2;
    if(currentFrame < totalFrames/2) {
      x = getX() + frameWidth - 40;

      vel[0] += minSpeed;
    }
    else {
      x=getX();

      vel[0] -= minSpeed;
    }
    vel[1] *=0;
    bullets.shoot(Vector2f(x,y), vel);

}
}

bool ShootingSprite::collidedWith(const Drawable* obj) const {
  if(obj){
	  
  return bullets.collidedWith( obj );
  
  }
  return false;
}

void ShootingSprite::draw() const {
  GhostPlayer::draw();
  bullets.draw();
}

void ShootingSprite::update(Uint32 ticks) {
  GhostPlayer::update(ticks);
  bullets.update(ticks);
}
