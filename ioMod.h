#ifndef IOMOD__H
#define IOMOD__H
#include <iostream>
#include <string>
#include <sstream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

class IOmod {
public:
  static IOmod& getInstance();
  ~IOmod();
  SDL_Texture* readTexture(const std::string& filename) const;
  SDL_Surface* readSurface(const std::string& filename);
  void writeText(const std::string&, int, int,SDL_Color txtcolor) const;
  void writeMessage(const std::string&, double,int , int) const;
  SDL_Renderer* getRenderer() const { return renderer; }


private:
  int init;
  SDL_Renderer* renderer;
  TTF_Font* font;
  SDL_Color textColor, txtColor;
  IOmod();
  IOmod(const IOmod&);
  IOmod& operator=(const IOmod&);
};
# endif
