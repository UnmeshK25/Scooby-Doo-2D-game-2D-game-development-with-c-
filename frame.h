
#ifndef FRAME__H
#define FRAME__H
#include <SDL.h>
#include <iostream>
#include <string>


class Frame {
public:
  
  Frame(SDL_Texture*);

  Frame(const Frame&);
  Frame& operator=(const Frame&);

  void draw(int x, int y) const;
  void draw(int sx, int sy, int dx, int dy) const;
  void draw(int x, int y, float scale) const;

  SDL_Texture * getTexture() const { return texture; }
  int getWidth()  const { return rect.w; }
  int getHeight() const { return rect.h; }
Frame* crop(SDL_Rect)const;

private:
  SDL_Renderer * renderer;
  SDL_Texture * texture;
SDL_Rect rect;
  Frame();
    
};

#endif
