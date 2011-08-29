
#ifndef __TimeTrackerImpl_h__
#define __TimeTrackerImpl_h__

class TimeTrackerImpl : public TimeTracker {
  
  int32_t time;
  int32_t lastConsumedTime;
  
  bool marked;
  bool expiredFlagRead;
  uint32_t markTime;
  
  bool pauseMarked;
  uint32_t pauseMarkTime;
  
public:

  TimeTrackerImpl() {
    time = 0;
    lastConsumedTime = 0;
    marked = false;
    markTime = 0;
    pauseMarked = false;
    pauseMarkTime = 0;
  }
  virtual ~TimeTrackerImpl() {
  }

  //<TimeTracker>
  
  virtual void setTime(int32_t time) {
    if( time > 0 ) {
      expiredFlagRead = false;
    }
    this->time = time;
  }

  virtual void addTime(int32_t delta) {
    setTime( time + delta );
  }
  
  virtual int32_t getTime(Clock *clock) {
    
    return time - elapsedTime( clock );
  }
  
  virtual int32_t getLastConsumedTime() {
    return lastConsumedTime;
  }
  
  //</TimeTracker>
  
  void mark(Clock *clock) {
    marked = true;
    markTime = clock->currentTime();
  }
  
  void consume(Clock *clock) {
    lastConsumedTime = elapsedTime( clock );
    marked = false;
    addTime( -lastConsumedTime );
  }
  
  bool onlyOnceIsExpired() {
    bool ret = !expiredFlagRead;
    expiredFlagRead = true;
    return ret;
  }
  
  void beginPause(Clock *clock) {
    pauseMarked = true;
    pauseMarkTime = clock->currentTime();
  }

  void endPause(Clock *clock) {
    pauseMarked = false;
    markTime = clock->currentTime() - ( pauseMarkTime - markTime );
  }

private:

  int32_t elapsedTime(Clock *clock) {
    if( pauseMarked ) {
      return  pauseMarkTime - markTime;
    }
    return marked ? clock->currentTime() - markTime : 0;
  }
  
};

#endif

