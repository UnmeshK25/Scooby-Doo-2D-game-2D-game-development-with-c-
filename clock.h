#include <SDL.h>
#include <string>

class Engine;

class Clock {
public:
  static Clock& getInstance();
  unsigned int getTicks() const;

  float getAvgFps() const;
  unsigned int getElapsedTicks();
  void pause();
    bool isPaused() const  { return paused;  }
unsigned int getSeconds() const { return getTicks()/1000;  }

private:
  friend class Engine;

  bool started;
  bool paused;

  const bool FRAME_CAP_ON;
  const Uint32 PERIOD;
  unsigned int FramesAvgfps;

  unsigned int frames;

  unsigned int timeAtStart;
  unsigned int timeAtPause;
  unsigned int currTicks;
  unsigned int prevTicks;
  unsigned int ticks;

  int getFps() const;
  void incrFrame();
  void toggleSloMo();

  bool isStarted() const { return started; }

  unsigned int getFrames() const  { return frames;  }
  
  unsigned int capFrameRate() const;


  void startClock();

  void unpause();

  Clock();
  Clock(const Clock&);
  Clock&operator=(const Clock&);
};
