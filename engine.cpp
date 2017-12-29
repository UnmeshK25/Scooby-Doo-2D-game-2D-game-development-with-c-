#include <iostream>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "gamedata.h"
#include "engine.h"
#include "ghostPlayer.h"
#include "frameGenerator.h"
#include "collisionStrategy.h"
#include "shootingSprite.h"
#include "health.h"

class ScaledSpritesInstances {
public:
  bool operator()(const Drawable* lhs, const Drawable* rhs) const {
    return lhs->getScale() < rhs->getScale();
  }
};

Engine::~Engine() {

  for(auto* sp : sprites)
      delete sp;
  for(auto* spr : sprites1){
      delete spr;
  }
    if(gamePlayer){
      delete gamePlayer;
      gamePlayer = NULL;
  }

 if(strategy)delete strategy;
 if(strategy1)delete strategy1;
 if(sprite) delete sprite;


}

Engine::Engine() :
  flag(false),
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  showHud(false),
  showHudbullet(true),
  playSound(true),
  collision(true),
  score(0),
  scoobyBack1("scoobyBack1", Gamedata::getInstance().getXmlInt("scoobyBack1/factor") ),
  scoobyBack2("scoobyBack2", Gamedata::getInstance().getXmlInt("scoobyBack2/factor") ),
  viewport( Viewport::getInstance() ),
  hud( Hud::getInstance() ),
  health( Health::getInstance() ),
  gamePlayer(new ShootingSprite("ghost")),
  sound(),
  hudTime( Gamedata::getInstance().getXmlInt("hudBar/time") ),
  
  sprites(),
  sprites1(),
  currentSprite(-1),

  makeVideo( false ),
  sprite(new Sprite("crown")),
  win(false),
   strategy( new PerPixelCollisionStrategy ),
   strategy1(new MidPointCollisionStrategy),
   textFontColor({0xff, 0xa5, 0, 0})
{
  SmartSprite *scoob =  new SmartSprite("scooby");
  SmartSprite *shabby =  new SmartSprite("shabby") ;
  SmartSprite *boy =  new SmartSprite("boy");
  sprites.push_back( scoob );
  sprites.push_back( shabby);
  sprites.push_back( boy );
  gamePlayer->attach(scoob);
  gamePlayer->attach(shabby);
  gamePlayer->attach(boy);


  unsigned int n = Gamedata::getInstance().getXmlInt("bat/noOfObjects/instances");
  static float scale = Gamedata::getInstance().getXmlFloat("bat/scale/min");
  for ( unsigned int i = 0; i < n; ++i ) {
    float diff= Gamedata::getInstance().getXmlFloat("bat/scale/max")-Gamedata::getInstance().getXmlFloat("bat/scale/min");

    float incr= diff/n;
    scale = scale+incr;
    auto* s = new ScaledSprite("bat",scale);

    s->setScale(scale);
    sprites1.push_back(s);
    gamePlayer->attach(s);
  }

  std::vector<Drawable*>::iterator ptr = sprites1.begin();
  sort(ptr, sprites1.end(), ScaledSpritesInstances());


  switchSprite();
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {

   scoobyBack1.draw();

   for(auto* s : sprites) s->draw();
   for(int i=0; i<((Gamedata::getInstance().getXmlInt("bat/noOfObjects/instances"))/2); i++) sprites1[i]->draw();
   scoobyBack2.draw();

   for(auto* s : sprites) s->draw();
   for(int i=6; i<(Gamedata::getInstance().getXmlInt("bat/noOfObjects/instances")); i++) sprites1[i]->draw();
 
   gamePlayer->draw();
   std::stringstream strm;
   std::stringstream strm1;
   health.HealthBarDraw();
    if(showHudbullet){
    hud.HudBulletPool();
  }
   
   if(clock.getSeconds() < hudTime || showHud){
    hud.HudRect();
  }

  sprite->draw();
  viewport.draw();
  if(win && score>=10)
  {
	  hud.HudWin();
      Clock::getInstance().pause();
	 }
	 if(!collision)IOmod::getInstance().writeText("God mode is on", 300, 60,textFontColor);
	 else if(collision)IOmod::getInstance().writeText("God mode is off", 300, 60,textFontColor);
	 IOmod::getInstance().writeMessage("Player's score: ",score, 300, 84);
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for(auto* s : sprites)
  s->update(ticks);

  for(auto* s : sprites1) s->update(ticks);
  checkForCollisions();
  
	if ( strategy1->execute(*gamePlayer, *sprite )){
		win=true;

}

  scoobyBack1.update();
  scoobyBack2.update();
  gamePlayer->update(ticks);
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % sprites.size();
  Viewport::getInstance().setObjectToTrack(gamePlayer);

}


void Engine::checkForCollisions() {

 std::vector<Drawable*>::const_iterator it = sprites1.begin();
 std::vector<Drawable*>::const_iterator itr = sprites1.begin();
 std::vector<Drawable*>::const_iterator it1 = sprites.begin();



for(int i=0;i<6;i++)
{
  it++;
  itr++;
}
if(collision)
{

while ( it != sprites1.end() ) {
  if ( strategy1->execute(*gamePlayer, **it) ) {

 
  static int count=0;
  count++;

      if(count==60)
      {
		  count=0;
		  Health::getInstance().decreaseHealth();
	  }
  }
  ++it;

}
}
  while ( it1 != sprites.end() ) {
	  if ( strategy1->execute(*gamePlayer, **it1) ){
		  if(playSound)
      sound[2];
    static_cast<ShootingSprite*>(gamePlayer)->explode();

   }
    ++it1;
  }
  
  while ( itr != sprites1.end() ) {
	   if ( static_cast<ShootingSprite*>(gamePlayer)->collidedWith(*itr) ) {
		   score++;
	
		   if(playSound)
       sound[2];
    static_cast<ScaledSprite*>(*itr)->explode();

    }
    ++itr;
  }

}


void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  bool keyCatch = false;

  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;
  clock.startClock();
  while ( !done ) {
	  keystate = SDL_GetKeyboardState(NULL);
      while ( SDL_PollEvent(&event) ) {
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYUP) {
        keyCatch = false;}
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {

          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_U] ) {
          clock.toggleSloMo();
        }
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
        }
        if ( keystate[SDL_SCANCODE_SPACE] ) {

          static_cast<ShootingSprite*>(gamePlayer)->shoot();
          if(playSound)
          sound[1];

        }
       if (keystate[SDL_SCANCODE_R] && !keyCatch) {
	
		 viewport.reset();
         clock.startClock();
         gamePlayer->resetPosition();
         health.reset();
         win=false;
         for(auto *s : sprites) static_cast<SmartSprite *> (s)->reset();
         keyCatch = true;
         score=0;
       }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
            std::cout << "Initiating frame capture" << std::endl;
            makeVideo = true;
          }
          else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
            std::cout << "Terminating frame capture" << std::endl;
            makeVideo = false;
          }
          if (keystate[SDL_SCANCODE_F1] && !keyCatch) {
            keyCatch = true;
            showHud = !showHud;
          }
          if (keystate[SDL_SCANCODE_F2]) {
            showHudbullet = !showHudbullet;
          }
          if (keystate[SDL_SCANCODE_G] && playSound && collision) {
			  playSound=false;
			  collision=false;
		
             gamePlayer->toggleGodMode();
       }
       else if (keystate[SDL_SCANCODE_G] && !playSound && !collision) {
			  playSound=true;
			  collision=true;
		
             gamePlayer->toggleGodMode();
       }
      }
    }

    if(keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_D])
    {
		gamePlayer->stop();

	}
	if(keystate[SDL_SCANCODE_W] && keystate[SDL_SCANCODE_S])
    {
		gamePlayer->stop();

	}
	else{
	if (keystate[SDL_SCANCODE_D] )
	{
        gamePlayer->gotoRight();

    }
    if (keystate[SDL_SCANCODE_A] )
	{
        gamePlayer->gotoLeft();

    }

    if (keystate[SDL_SCANCODE_S] )
    {
        gamePlayer->gotoDown();

    }
    if (keystate[SDL_SCANCODE_W] )
    {
	    gamePlayer->gotoUp();

    }
     
}
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }

}
