 #include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "hud.h"
#include "health.h"
#include "scaledSprite.h"
#include "ghostPlayer.h"
#include "sprite.h"
#include "sound.h"


class CollisionStrategy;
class GhostPlayer;
class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  void switchSprite();
  bool flag;


private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  bool showHud;
  bool showHudbullet;
  bool playSound;
  bool collision;
  int score;
  World scoobyBack1;
  World scoobyBack2;
  Viewport& viewport;
  Hud& hud;
  Health& health;
  GhostPlayer* gamePlayer;
   SDLSound sound;


  unsigned int hudTime;
  std::vector<Drawable*> sprites;
  std::vector<Drawable*> sprites1;

  int currentSprite;

  bool makeVideo;
  Sprite *sprite;
  bool win;
  CollisionStrategy* strategy;
  CollisionStrategy* strategy1;
  SDL_Color textFontColor;
  void draw() const;
  void update(Uint32);

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  void checkForCollisions();
};
