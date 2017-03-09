typedef struct Timer
{
        char OnDelayReached;
        unsigned int duration;
        unsigned int inc;
} Timer;

void UpdateTimer(Timer* __timer)
{
        ++(__timer->inc) %= __timer->duration+1;
        __timer->OnDelayReached = (__timer->inc >= __timer->duration);
}

void UpdateTimers(Timer* timers, char _size)
{
 char i;
 for(i=0; i<_size; i++)
          UpdateTimer(timers+i);
}

void SetTimer(Timer* _timer, int _dur)
{
  _timer->OnDelayReached = 0;
  _timer->inc = 0;
  _timer->duration = _dur;
}