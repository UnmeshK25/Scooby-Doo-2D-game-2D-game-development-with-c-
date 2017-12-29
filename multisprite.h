#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"
#include "sprite.h"
#include "frame.h"
#include "explodingSprite.h"

class CollisionStrategy;
class Sprite;
class MultiSprite : public Drawable {
	
public:
  MultiSprite(const std::string&);
  MultiSprite(const std::string&,float);
  MultiSprite(const MultiSprite&);
  ~MultiSprite(){
  	if(boom){
  		delete boom;
  	}
  }

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual void reset();
  virtual const Frame* getFrame() const {
    return frames[currentFrame];

  }

private:
  ExplodingSprite* boom;
  bool explosion;
	Vector2f genVelocity(int,int,std::string) const;
	Vector2f makeVelocity(int, int,float) const;
 MultiSprite& operator=(const MultiSprite&);
 
protected:
  const std::vector<Frame *> frames;
  unsigned currentFrame;
  std::string spritename;
  unsigned totalFrames;
  unsigned frameInterval;
  float lastFrameTime;
  int worldWidth;
  int worldHeight;
  int frameWidth;
  int frameHeight;

  void advanceFrame(Uint32 ticks);
};
#endif
