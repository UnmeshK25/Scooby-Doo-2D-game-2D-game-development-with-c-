#include "hud.h"
#include "ioMod.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "gamedata.h"
#include "renderContext.h"
#include "clock.h"


Hud& Hud::getInstance(){
    static Hud instance;
    return instance;
}

Hud::Hud():

	poolSize(0),
    abSize(0),
    hudWidth(Gamedata::getInstance().getXmlInt("hudBar/width")),
    hudHeight(Gamedata::getInstance().getXmlInt("hudBar/height")),
    hudWidth1(Gamedata::getInstance().getXmlInt("hudBar/width1")),
    hud_x(Gamedata::getInstance().getXmlInt("hudBar/startLoc/x")),
    hud_y(Gamedata::getInstance().getXmlInt("hudBar/startLoc/y")),
    hudloss_x(Gamedata::getInstance().getXmlInt("hudLoss/startLoc/x")),
    hudloss_y(Gamedata::getInstance().getXmlInt("hudLoss/startLoc/y")),
    hudWidthloss(Gamedata::getInstance().getXmlInt("hudLoss/losswidth")),
    hudHeightloss(Gamedata::getInstance().getXmlInt("hudLoss/lossheight")),
    hudwin_x(Gamedata::getInstance().getXmlInt("hudWin/startLoc/x")),
    hudwin_y(Gamedata::getInstance().getXmlInt("hudWin/startLoc/y")),
    hudWidthwin(Gamedata::getInstance().getXmlInt("hudWin/winwidth")),
    hudHeightwin(Gamedata::getInstance().getXmlInt("hudWin/winheight")),
    hudRect({hud_x,hud_y,hudWidth,hudHeight}),
    hudRect1({hudloss_x,hudloss_y,hudWidthloss,hudHeightloss}),
    hudRect2({hudwin_x,hudwin_y,hudWidthwin,hudHeightwin}),
    hudRect3({hudwin_x+50,hudwin_y+100,hudWidthwin-20,hudHeightwin+30}),
    renderer( RenderContext::getInstance()->getRenderer() ),
    textFontColor({0xff, 0xa5, 0, 0})
{}

Hud::~Hud()
{}

SDL_Texture* Hud::readTexture(const std::string& filename) const{
  SDL_Texture *texture = IMG_LoadTexture(renderer, filename.c_str());
  if ( texture == NULL ) {
    throw std::string("Couldn't load ") + filename;
  }
  return texture;
}


void Hud::HudRect() const{

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
    const double elapsedSeconds= (double)(Clock::getInstance().getSeconds());
    const double avgFPS=(double)(Clock::getInstance().getAvgFps());
    // Render rect
    SDL_RenderFillRect( renderer, &hudRect );

    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &hudRect );
    IOmod::getInstance().writeText("A -> To move LEFT  ", hud_x+20, hud_y+15,textFontColor);
    IOmod::getInstance().writeText("D->  To move RIGHT ", hud_x+20, hud_y+40,textFontColor);
    IOmod::getInstance().writeText("W -> To move UP    ", hud_x+20, hud_y+62,textFontColor);
    IOmod::getInstance().writeText("S ->  To move DOWN ", hud_x+20, hud_y+84,textFontColor);
    IOmod::getInstance().writeMessage("Elapsed Seconds: ", elapsedSeconds, hud_x+20, hud_y+107);
    IOmod::getInstance().writeMessage("Average fps: ", avgFPS, hud_x+20, hud_y+129);
    IOmod::getInstance().writeText("F1-> For toggle HUD", hud_x+20, hud_y+151,textFontColor);
    IOmod::getInstance().writeText("F4 -> to generate frames", hud_x+20, hud_y+174,textFontColor);
    IOmod::getInstance().writeText("Press Space bar to shoot", hud_x+20, hud_y+200,textFontColor);
    IOmod::getInstance().writeText("G -> To enable God mode", hud_x+20, hud_y+227,textFontColor);
    IOmod::getInstance().writeText("R -> To reset/restart game", hud_x+20, hud_y+254,textFontColor);
}

void Hud::HudLoss() const{

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( renderer, &hudRect1 );
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &hudRect1 );
    IOmod::getInstance().writeText("Game Over  ", 260, 215,textFontColor);
    IOmod::getInstance().writeText("You Lost ", 260, 240,textFontColor);
    IOmod::getInstance().writeText("Press R to restart game ", 260, 266,textFontColor);
}

void Hud::HudLife(int life) const{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( renderer, &hudRect2 );
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &hudRect2 );
    IOmod::getInstance().writeMessage("Ghost lives remaining: ", life, 530, 40);
}

void Hud::HudBulletPool() const{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( renderer, &hudRect3 );
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &hudRect3 );
    IOmod::getInstance().writeMessage("Active bullets: ", abSize, hudwin_x+70, hudwin_y+110);
    IOmod::getInstance().writeMessage("Bullet pool: ", poolSize, hudwin_x+70, hudwin_y+135);
    IOmod::getInstance().writeText("F2-> For toggle HUD", hudwin_x+70, hudwin_y+160,textFontColor);
}

void Hud::HudWin() const{

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( renderer, &hudRect1 );
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &hudRect1 );
    IOmod::getInstance().writeText("Game Over  ", 260, 215,textFontColor);
    IOmod::getInstance().writeText("You Won the game!!! ", 260, 240,textFontColor);
	IOmod::getInstance().writeText("Press R to restart game ", 260, 266,textFontColor);
}
