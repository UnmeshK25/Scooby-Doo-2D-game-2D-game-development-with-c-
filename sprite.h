#ifndef SPRITE__H
#define SPRITE__H
#include <string>
#include "drawable.h"
#include "frame.h"


class Sprite : public Drawable {
public:
  Sprite(const std::string&);
  Sprite(const std::string&,const Frame*);
  Sprite(const std::string&, const Vector2f& pos, const Vector2f& vel, const Frame*);
  Sprite(const Sprite&);
  virtual ~Sprite() { } 
  Sprite& operator=(const Sprite&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void setFrame(const Frame* frm) { frame=frm; }
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  void explode();
  

private:
  const Frame * frame;
  int worldWidth;
  int worldHeight;
  int frameWidth;
  int frameHeight;

  int getDistance(const Sprite*) const;

};
#endif
