
#ifndef __TimeTrackerImpl_h__
#define __TimeTrackerImpl_h__

class TimeTrackerImpl : public TimeTracker {
  
  int32_t time;
  int32_t lastConsumedTime;
  
  bool marked;
  uint32_t markTime;
  
public:

  TimeTrackerImpl() {
    time = 0;
    lastConsumedTime = 0;
    marked = false;
    markTime = 0;
  }
  virtual ~TimeTrackerImpl() {
  }

  //<TimeTracker>
  
  void setTime(int32_t time) {
    this->time = time;
  }

  void addTime(int32_t delta) {
    setTime( time + delta );
  }
  
  int32_t getTime(Clock *clock) {
    return time - elapsedTime( clock );
  }
  
  int32_t getLastConsumedTime() {
    return lastConsumedTime;
  }
  
  //</TimeTracker>
  
  void mark(Clock * clock) {
    marked = true;
    markTime = clock->currentTime();
  }
  
  void consume(Clock * clock) {
    lastConsumedTime = elapsedTime( clock );
    marked = false;
    addTime( -lastConsumedTime );
  }

private:

  int32_t elapsedTime(Clock *clock) {
    return marked ? clock->currentTime() - markTime : 0;
  }
  
};

#endif

