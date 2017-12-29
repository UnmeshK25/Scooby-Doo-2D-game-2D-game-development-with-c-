#ifndef RENDERCONTEXT__H
#define RENDERCONTEXT__H
#include <iostream>
#include <SDL.h>
#include "frameFactory.h"


const int DELAY = 1000;

class RenderContext{
public:
  static RenderContext* getInstance();
  ~RenderContext();
  SDL_Window* getWindow() const { return window; }
  SDL_Renderer* getRenderer() const { return renderer; }

  Frame* getFrame(const std::string& n) { 
    return FrameFactory::getInstance()->getFrame(n);
  }
  std::vector<Frame*> getFrames(const std::string& n) {
    return FrameFactory::getInstance()->getFrames(n);
  }

  SDL_Surface* getSurface(const std::string& n) { 
    return FrameFactory::getInstance()->getSurface(n);
  }
  
  
private:
  static RenderContext* instance;
  const Gamedata& gamedata;
  int WIDTH;
  int HEIGHT;
  SDL_Window* window;
  SDL_Renderer* renderer;

  FrameFactory factory;
  SDL_Window* initWindow();
  SDL_Renderer* initRenderer();
  RenderContext();
  RenderContext(const RenderContext&) = delete;
  RenderContext& operator=(const RenderContext&) = delete;
};
#endif
