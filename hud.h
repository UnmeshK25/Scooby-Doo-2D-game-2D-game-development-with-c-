#include <string>
#include <SDL.h>
#include <stdint.h>

class Hud {
public:
  static Hud& getInstance();
  ~Hud();

  void HudRect() const;
  void HudLoss() const;
  void HudLife(int) const;
  void HudBulletPool() const;
  void HudWin() const;
  void setBulletpool(int bSize){poolSize=bSize;}
  int getBulletpool(){return poolSize;}
  void setActiveBullets(int activeBsize){abSize=activeBsize;}
  int getActiveBullets(){return abSize;}
  SDL_Renderer* getRenderer() const { return renderer; }
  SDL_Texture* readTexture(const std::string& filename) const;

  int poolSize;
  int abSize;
  
private:
  const int hudWidth;
  const int hudHeight;
  const int hudWidth1;
  int hud_x;
  int hud_y;
  int hudloss_x;
  int hudloss_y;
  const int hudWidthloss;
  const int hudHeightloss;
  int hudwin_x;
  int hudwin_y;
  const int hudWidthwin;
  const int hudHeightwin;
  SDL_Rect hudRect;
  SDL_Rect hudRect1;
  SDL_Rect hudRect2;
  SDL_Rect hudRect3;
  SDL_Renderer* renderer;
  Hud();
  Hud(const Hud&);
  Hud& operator=(const Hud&);
  SDL_Color textFontColor;

};
