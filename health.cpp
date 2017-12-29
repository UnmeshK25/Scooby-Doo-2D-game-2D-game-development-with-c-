#include "health.h"
#include "ioMod.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "gamedata.h"
#include "renderContext.h"
#include "clock.h"

Health& Health::getInstance(){
    static Health instance;
    return instance;
}

Health::Health():

    healthWidth(Gamedata::getInstance().getXmlInt("healthBar/healthwidth")),
    healthHeight(Gamedata::getInstance().getXmlInt("healthBar/healthheight")),
    health_x(Gamedata::getInstance().getXmlInt("healthBar/startLoc/x")),
	health_y(Gamedata::getInstance().getXmlInt("healthBar/startLoc/y")),
	healthRect({health_x,health_y,healthWidth,healthHeight}),
    healthRect1({health_x,health_y,healthWidth,healthHeight}),
    incDec(Gamedata::getInstance().getXmlInt("healthBar/incrdecr")),
    renderer( RenderContext::getInstance()->getRenderer() ),
    textFontColor({0xff, 0xa5, 0, 0})
{}

Health::~Health()

{}


void Health::HealthBarDraw() const{

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 0, 255, 0, 125 );

    SDL_RenderFillRect( renderer, &healthRect1 );
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &healthRect );
    IOmod::getInstance().writeMessage("Health: ", healthRect1.w/2, health_x+10, health_y+5);
}

void Health::increaseHealth() {

  healthRect1.w= healthRect1.w+incDec;
  if(healthRect1.w>=healthWidth)
    {healthRect1.w = healthWidth;}

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255/2 );   
    SDL_RenderFillRect( renderer, &healthRect1 );
}

void Health::decreaseHealth() {

  healthRect1.w=healthRect1.w-incDec;
    if(healthRect1.w <=0){
      healthRect1.w = 0;
    }

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor( renderer, 0, 255, 0, 125 );
 
  SDL_RenderFillRect( renderer, &healthRect1 );

}

void Health::reset() {

healthRect1.w=healthWidth;

}
