#include "multisprite.h"
#include "gamedata.h"
#include "renderContext.h"
#include "explodingSprite.h"
#include "collisionStrategy.h"


Vector2f MultiSprite::genVelocity(int velX, int velY, std::string name1) const
{

	float m= Gamedata:: getInstance().getRandInRange(velX-50, velX+50);
	float n= Gamedata:: getInstance().getRandInRange(velY-50, velY+50);
	if(name1=="bat")
	{
		velX+= m;
		velY+= n;
	    return Vector2f(m,n);
	}
	return Vector2f(velX,velY);
}

Vector2f MultiSprite::makeVelocity(int vx, int vy,float scale1) const {

  float v_rad = (scale1+0.7)*vx;
  float v_mag = (scale1+0.7)*vy;
  return Vector2f(v_rad,v_mag);
}

MultiSprite::MultiSprite( const std::string& name) :
  
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),

						genVelocity(Gamedata::getInstance().getXmlInt(name+"/speedX"),
						Gamedata::getInstance().getXmlInt(name+"/speedY"),name)
           ),
            boom(NULL),
           explosion(false),
  frames( RenderContext::getInstance()->getFrames(name) ),
  currentFrame(0),
  spritename(name),
  totalFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  lastFrameTime( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())

{}


MultiSprite::MultiSprite( const std::string& name, float sc1) :
   
 Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x")+(sc1*700),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")+(sc1*100)),
           makeVelocity(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"),sc1)
           ),
           boom(NULL),
           explosion(false),
  frames( RenderContext::getInstance()->getFrames(name) ),
  currentFrame(0),
  spritename(name),
  totalFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  lastFrameTime( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
	
{
setScale(sc1);
std::cout<<sc1<<std::endl;
}


MultiSprite::MultiSprite(const MultiSprite& s) :
  
  Drawable(s),
  boom(s.boom),
   explosion(s.explosion),
  frames(s.frames),
  currentFrame(s.currentFrame),
  spritename(s.spritename),
  totalFrames( s.totalFrames ),
  frameInterval( s.frameInterval ),
  lastFrameTime( s.lastFrameTime ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight )

  { }



void MultiSprite::advanceFrame(Uint32 ticks) {
    lastFrameTime += ticks;
if (lastFrameTime > frameInterval) {
	if (getVelocityX() < 0){
            if (currentFrame <= totalFrames / 2) {
				//currentFrame = (currentFrame + (totalFrames / 2) + 1) % totalFrames;
                while(currentFrame <= totalFrames / 2){
					currentFrame = (currentFrame + (totalFrames / 2) + 1) % totalFrames;
				}
            }
            else{
                currentFrame = (currentFrame + 1) % totalFrames;

                while(currentFrame <= totalFrames / 2){
					currentFrame = (currentFrame + (totalFrames / 2) + 1) % totalFrames;
				}
            }
        }

        else  if (getVelocityX() >= 0) {
            currentFrame = (currentFrame + 1) % (totalFrames/2);
        }
        lastFrameTime = 0;
    }
}

void MultiSprite::draw() const {

		frames[currentFrame]->draw(getX(), getY());

}

void MultiSprite::update(Uint32 ticks) {

  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-frameHeight) {
    setVelocityY( -fabs( getVelocityY() ) );
  }
  float maxX = 1.0;

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > maxX * worldWidth-frameWidth) {
    setVelocityX( -fabs( getVelocityX() ) );
  }

}

void MultiSprite::reset()
{
   setX(Gamedata::getInstance().getXmlInt(getName()+"/startLoc/x"));

   setY(Gamedata::getInstance().getXmlInt(getName()+"/startLoc/y"));
   setVelocity(Vector2f(Gamedata::getInstance().getXmlInt(getName()+"/speedX"),
                    Gamedata::getInstance().getXmlInt(getName()+"/speedY")));

}
