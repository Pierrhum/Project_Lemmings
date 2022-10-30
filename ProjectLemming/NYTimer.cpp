#include "NYTimer.h"

void NYTimer::start()
{
    QueryPerformanceCounter(&lastUpdateTime);
}

void NYTimer::restart(int MaxTime)
{
    _MaxTime = MaxTime;

    LARGE_INTEGER timeNow;
    QueryPerformanceCounter(&timeNow);
    lastUpdateTime = timeNow;
}

float NYTimer::getElapsedSeconds()
{
    LARGE_INTEGER timeNow;
    QueryPerformanceCounter(&timeNow);
    LONGLONG elapsedLong = timeNow.QuadPart-lastUpdateTime.QuadPart;

    float elapsed = (float) ((float)elapsedLong/(float)freq);
    elapsed /= 1000.0f;

    return elapsed;
}

unsigned long NYTimer::getElapsedMs()
{
    LARGE_INTEGER timeNow;
    QueryPerformanceCounter(&timeNow);
    LONGLONG elapsedLong = timeNow.QuadPart-lastUpdateTime.QuadPart;

    unsigned long elapsed = (unsigned long) ((float)elapsedLong/(float)freq);
    return elapsed;
}

int NYTimer::getRemainingTime()
{
    return _MaxTime - (int)getElapsedSeconds();     
}
