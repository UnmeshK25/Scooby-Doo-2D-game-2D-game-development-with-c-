#ifndef GHOSTPLAYER__H
#define GHOSTPLAYER__H
#include <string>
#include <vector>
#include <list>
#include "multisprite.h"
#include "explodingSprite.h"
#include "health.h"
#include "smartSprite.h"


class GhostPlayer : public MultiSprite {
public:

  GhostPlayer(const std::string&);
  GhostPlayer(const GhostPlayer&);

  virtual ~GhostPlayer(){
    if(boom){ delete boom; }
    std::list<SmartSprite*>::iterator itr= observers.begin();
    while(itr!=observers.end())
    {
		itr=observers.erase(itr);
		itr++;
		}
  
  };
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  
  void stop();
  void gotoLeft();
  void gotoRight();
  void gotoUp();
  void gotoDown();
  void explode();
  void resetPosition();
  void attach( SmartSprite* o ) { observers.push_back(o); }
  void detach( SmartSprite* o );
  void notify();

  void toggleGodMode(){ godMode = !godMode; }
  bool explosion;
  int life_cnt;
  void setLife(int life){life_cnt=life;}
  int getLife()const{return life_cnt;}

private:
  Vector2f initVelocity;

  ExplodingSprite* boom;

  bool godMode;
  std::list<SmartSprite*> observers;
  GhostPlayer& operator=(const GhostPlayer&);


};

#endif
